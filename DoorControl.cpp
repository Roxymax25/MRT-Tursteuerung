/*
 * Praktikum MRT2 
 * ART1 Türsteuerung
 * Institut für Automatisierungstechnik
 * letztes Update Mai 2018
 * Autor: M.Herhold
 * Version: r2
 */

#include "DoorInterface.h"
#include "DoorControl.h"
#include "Automat.h"
#include "Zustaende.h"
#include "Automaten_Funktionen.h"
#include "Transition.h"
#include <vector>
#include <map>



DoorControl::DoorControl() :    HUD(false, true),
                                Hand(),
                                Automatik(),
                                Rep(),
								config()



{
	// constructor
	// ... maybe, insert your sensor and actor initialization here?
    config.Konfiguration_einlesen();
    set_config(config);


}

DoorControl::~DoorControl()
{
	// destructor
	HUD.quit_doorcontrol_flag = true;
}

void DoorControl::run(){

	std::string msg;		// temporary variable to construct message
    unsigned int time = 0;
	unsigned delay_ms = 20;		// Milliseconds to wait on one loop

    Handbetrieb_einrichten();
    Automatikbetrieb_einrichten();
    Reperaturbetrieb_einrichten();
    int Au=0,Ha=0,Re=0;

    while((!HUD.quit_doorcontrol_flag)) {
        msg = "";
        bool BW1 = config.sensor_liste.at(0)->getPin();
        bool BW2 = config.sensor_liste.at(1)->getPin();
        Sensor_update();
        // 00-aus 01-Rep 10-Hand 11-Automatik
        if (!BW1 && !BW2) {
            //alle Aktoren 0
            Aktoren_aus();
        } else if (!BW1 && BW2) {
            if (Au == 1 || Ha == 1) {
                Rep->restart();
                Au = 0;
                Ha = 0;
            }
            Re = 1;
            Rep->run();
            //reperatur nächste Transitions
        } else if (BW1 && !BW2) {
            if (Au == 1 || Re == 1) {
                Hand->restart();
                Au = 0;
                Re = 0;
            }
            Ha = 1;
            Hand->run();
            //Hand nächste Transition
        } else if (BW1 && BW2) {
            if (Ha == 1 || Re == 1) {
                Automatik->restart();
                Re = 0;
                Ha = 0;
            }
            if (Au == 0) {
                config.aktor_liste.at(2)->setPin(true);
                Aktor_update();
                usleep(5000 * 1000); //5s
                config.aktor_liste.at(2)->setPin(false);
                Aktor_update();//5s blinken
                //Automatik->setZustand(*Automatikzustaende["Oeffnen"]);
            }
            Au = 1;
            Automatik->run();
        }
        /*if((config.aktor_liste.at(0)->getPin() && config.aktor_liste.at(1)->getPin())
            || (config.aktor_liste.at(1)->getPin() && config.sensor_liste.at(6)->getPin())
            || (config.aktor_liste.at(0)->getPin() && config.sensor_liste.at(4)->getPin())) {

            msg += "Fehler! Verklemmung!!";
            config.aktor_liste.at(0)->setPin(0);
            config.aktor_liste.at(1)->setPin(0);
            config.aktor_liste.at(2)->setPin(1);
        }*/
        Aktor_update();



        //construct counter message

        //msg = "press 'q', or wait ";
        // msg  += std::to_string(config.sensor_liste.at(3)->getPin());
        msg += "Auto Z: ";
        msg += Automatik->getZustand();
        //msg += " ";
        //msg += "Rep Z: ";
        //msg += Rep->getZustand();
        //msg += " ";
        //msg += std::to_string((int)((delay_ms*time)/1000));
        //msg += " seconds to quit";

        // set current message to be displayed by user interface
        HUD.DebugString(msg);

        // wait some time
        usleep(delay_ms * 1000);

        update_Timer(delay_ms);
        time++;
    }
}

void DoorControl::Sensor_update(){

        HUD.DIO_Read(0, &port0);
        HUD.DIO_Read(1, &port1);

        for (int i=0; i < 15; i++) {
            if (i < 8) {
                config.sensor_liste.at(i)->setPin((port0 >> i) & 1);
            }
            if(i > 7) {
                config.sensor_liste.at(i)->setPin((port1 >> (i-8) & 1));
            }
        }
}

void DoorControl::Aktor_update() {
        if (!(config.aktor_liste.at(0)->getPin())) {
            port2 &= ~(1 << 0);
        }
        if ((config.aktor_liste.at(0)->getPin())) {
            port2 |= (1 << 0);
        }
        if (!(config.aktor_liste.at(1)->getPin())) {
            port2 &= ~(1 << 1);
        }
        if ((config.aktor_liste.at(1)->getPin())) {
            port2 |= (1 << 1);
        }
        if (!(config.aktor_liste.at(2)->getPin())) {
            port2 &= ~(1 << 2);
        }
        if ((config.aktor_liste.at(2)->getPin())) {
            port2 |= (1 << 2);
        }
        HUD.DIO_Write(2,port2);

}

void DoorControl::Handbetrieb_einrichten() {

    Handzustaende["Stopp"] = new Zustaende(Aktoren_aus,Motoren_aus,Nichts ,"Stopp");
    Handzustaende["Auf"] = new Zustaende(Aktoren_aus,Motoren_aus,Nichts ,"Auf");
    Handzustaende["Zu"] = new Zustaende(Aktoren_aus,Motoren_aus,Nichts ,"Zu");
    Handzustaende["Oeffnen"] = new Zustaende(Tuer_auf,Tuer_auf,Nichts ,"Oeffnen");
    Handzustaende["Schliessen"] = new Zustaende(Tuer_zu,Tuer_zu,Nichts ,"Schliessen");

    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Oeffnen"],*Handzustaende["Stopp"], Kein_Knopf));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Schliessen"],*Handzustaende["Stopp"], Kein_Knopf));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Oeffnen"],*Handzustaende["Schliessen"], nur_NTZ));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Stopp"],*Handzustaende["Schliessen"], nur_NTZ));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Schliessen"],*Handzustaende["Oeffnen"], nur_NTA));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Stopp"],*Handzustaende["Oeffnen"], nur_NTA));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Schliessen"],*Handzustaende["Zu"], nur_ELG));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Schliessen"],*Handzustaende["Zu"], ELG_und_NTZ));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Oeffnen"],*Handzustaende["Zu"], ELG_und_NTZ));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Zu"],*Handzustaende["Oeffnen"], ELG_und_NTA));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Schliessen"],*Handzustaende["Oeffnen"], ELG_und_NTA));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Oeffnen"],*Handzustaende["Auf"], nur_ELO));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Oeffnen"],*Handzustaende["Auf"], ELO_und_NTA));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Auf"],*Handzustaende["Schliessen"], ELO_und_NTZ));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Oeffnen"],*Handzustaende["Schliessen"], ELO_und_NTZ));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Schliessen"],*Handzustaende["Auf"], ELO_und_NTA));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Zu"],*Handzustaende["Auf"], nur_ELO));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Auf"],*Handzustaende["Zu"], nur_ELG));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Stopp"],*Handzustaende["Auf"], nur_ELO));
    Transitionstabelle_Hand.push_back(new Transition (*Handzustaende["Stopp"],*Handzustaende["Zu"], nur_ELG));

    Hand = new Automat(*Handzustaende["Stopp"], Transitionstabelle_Hand);

}

void DoorControl::Automatikbetrieb_einrichten() {

    Automatikzustaende["Auf"] = new Zustaende(enter_Auto_Auf,Motoren_aus,Nichts ,"Auf");
    Automatikzustaende["Zu"] = new Zustaende(Motoren_aus,Motoren_aus,Nichts ,"Zu");
    Automatikzustaende["Oeffnen"] = new Zustaende(Tuer_auf,Tuer_auf,Nichts ,"Oeffnen");
    Automatikzustaende["Schliessen"] = new Zustaende(Tuer_zu,Tuer_zu,Nichts ,"Schliessen");

    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Oeffnen"],*Automatikzustaende["Schliessen"], nur_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Oeffnen"], nur_X));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Oeffnen"], X_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Zu"], nur_ELG));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Zu"], ELG_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Zu"],*Automatikzustaende["Oeffnen"], ELG_und_X));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Oeffnen"], ELG_und_X));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Oeffnen"], ELG_und_X_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Zu"],*Automatikzustaende["Oeffnen"], ELG_und_X_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Oeffnen"],*Automatikzustaende["Zu"], ELG_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Oeffnen"],*Automatikzustaende["Auf"], nur_ELO));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Auf"],*Automatikzustaende["Schliessen"], Automatik_Auf_Schliessen));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Oeffnen"],*Automatikzustaende["Schliessen"], ELG_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Oeffnen"],*Automatikzustaende["Auf"], ELO_und_X));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Auf"], ELO_und_X));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Schliessen"],*Automatikzustaende["Auf"], ELO_und_X_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Oeffnen"],*Automatikzustaende["Auf"], ELO_und_X_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Zu"],*Automatikzustaende["Auf"], nur_ELO));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Auf"],*Automatikzustaende["Zu"], nur_ELG));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Auf"],*Automatikzustaende["Schliessen"], ELO_und_NTZ));
    Transitionstabelle_Automatik.push_back(new Transition (*Automatikzustaende["Oeffnen"],*Automatikzustaende["Schliessen"], ELO_und_NTZ));


    Automatik = new Automat(*Automatikzustaende["Oeffnen"], Transitionstabelle_Automatik);

}

void DoorControl::Reperaturbetrieb_einrichten() {

    Repzustaende["Auf"] = new Zustaende(Motoren_aus,Motoren_aus,Nichts ,"Auf");
    Repzustaende["Zu"] = new Zustaende(Motoren_aus,Motoren_aus,Nichts ,"Zu");
    Repzustaende["Oeffnen"] = new Zustaende(Tuer_auf,Tuer_auf,Nichts ,"Oeffnen");
    Repzustaende["Schliessen"] = new Zustaende(Tuer_zu,Tuer_zu,Nichts ,"Schliessen");
    Repzustaende["Stopp"] = new Zustaende(Motoren_aus,Motoren_aus,Nichts ,"Stopp");

    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Oeffnen"],*Repzustaende["Stopp"], Keine_Eingabe));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Stopp"], Keine_Eingabe));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Oeffnen"],*Repzustaende["Schliessen"], nur_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Stopp"],*Repzustaende["Schliessen"], nur_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Oeffnen"], nur_X));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Stopp"],*Repzustaende["Oeffnen"], nur_X));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Zu"], nur_ELG));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Zu"], ELG_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Oeffnen"],*Repzustaende["Zu"], ELG_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Zu"],*Repzustaende["Oeffnen"], ELG_und_X_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Oeffnen"], ELG_und_X_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Zu"],*Repzustaende["Oeffnen"], ELG_und_X));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Oeffnen"], ELG_und_X));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Oeffnen"],*Repzustaende["Auf"], nur_ELO));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Auf"],*Repzustaende["Schliessen"], ELO_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Oeffnen"],*Repzustaende["Schliessen"], ELO_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Auf"], ELO_und_X));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Oeffnen"],*Repzustaende["Auf"], ELO_und_X));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Schliessen"],*Repzustaende["Auf"], ELO_und_X_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Oeffnen"],*Repzustaende["Auf"], ELO_und_X_und_NTZ));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Zu"],*Repzustaende["Auf"], nur_ELO));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Auf"],*Repzustaende["Zu"], nur_ELG));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Stopp"],*Repzustaende["Auf"], nur_ELO));
    Transitionstabelle_Rep.push_back(new Transition (*Repzustaende["Stopp"],*Repzustaende["Zu"], nur_ELG));

    Rep = new Automat(*Repzustaende["Stopp"], Transitionstabelle_Rep);

}
