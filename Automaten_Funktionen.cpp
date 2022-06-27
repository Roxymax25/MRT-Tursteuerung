//
// Created by Jonas on 18.06.2022.
//

#include "Automaten_Funktionen.h"

Konfiguration config;

unsigned int Timer = 0;
unsigned int verzoegerung = 3000;

void set_config(Konfiguration Konfig){
    config = Konfig;
}
void update_Timer(unsigned int delay){
    Timer += delay;
}


bool get_X(){
    return ((config.sensor_liste.at(8)->getPin()) || (config.sensor_liste.at(9)->getPin()) ||
           (config.sensor_liste.at(7)->getPin()) || (config.sensor_liste.at(2)->getPin()));
}

bool ELG_und_NTA(){
    return config.sensor_liste.at(2)->getPin() && config.sensor_liste.at(6)->getPin();
}
bool nur_NTZ(){
    return (config.sensor_liste.at(3)->getPin()) && (!(config.sensor_liste.at(6)->getPin()) &&
            !(config.sensor_liste.at(4)->getPin()) && !get_X());
}
bool nur_NTA(){
    return (config.sensor_liste.at(2)->getPin()) && !(config.sensor_liste.at(6)->getPin()) &&
                                                        !(config.sensor_liste.at(3)->getPin()) &&
                                                        !(config.sensor_liste.at(4)->getPin()) &&
                                                        !(config.sensor_liste.at(7)->getPin()) &&
                                                        !(config.sensor_liste.at(8)->getPin()) &&
                                                        !(config.sensor_liste.at(9)->getPin());
}
bool nur_X(){
    return (get_X() && !(config.sensor_liste.at(6)->getPin())
    		&& !(config.sensor_liste.at(4)->getPin())
			&& !(config.sensor_liste.at(3)->getPin()));
}
bool X_und_NTZ(){
    return (get_X() && !(config.sensor_liste.at(6)->getPin())
    		&& !(config.sensor_liste.at(4)->getPin())
			&& (config.sensor_liste.at(3)->getPin()));
}
bool ELG_und_X(){
    return (get_X() && !(config.sensor_liste.at(3)->getPin())
    		&& !(config.sensor_liste.at(4)->getPin())
			&& (config.sensor_liste.at(6)->getPin()));
}
bool ELG_und_X_und_NTZ(){
    return (get_X() && (config.sensor_liste.at(3)->getPin()
    		&& (config.sensor_liste.at(6)->getPin())
			&& !(config.sensor_liste.at(4)->getPin())));
}
bool ELO_und_X_und_NTZ(){
    return (get_X() && (config.sensor_liste.at(3)->getPin())
    		&& (config.sensor_liste.at(4)->getPin())
			&& !(config.sensor_liste.at(6)->getPin()));
}
bool ELO_und_X(){
    return (get_X() && !(config.sensor_liste.at(3)->getPin())
    		&& !(config.sensor_liste.at(6)->getPin())
			&& (config.sensor_liste.at(4)->getPin()));
}
bool nur_ELG(){
    return ((config.sensor_liste.at(6)->getPin() )
    		&& !(config.sensor_liste.at(3)->getPin())

			&& !(config.sensor_liste.at(4)->getPin()) && !(get_X()));
}
bool ELG_und_NTZ(){
    return (config.sensor_liste.at(6)->getPin())
    		&& (config.sensor_liste.at(3)->getPin());
}
bool nur_ELO(){
    return ((config.sensor_liste.at(4)->getPin())
    		&& (!(config.sensor_liste.at(3)->getPin()) && !(config.sensor_liste.at(6)->getPin()) && !get_X()));
}
bool ELO_und_NTZ(){
    return ((config.sensor_liste.at(4)->getPin()) && (config.sensor_liste.at(3)->getPin()));
}
bool ELO_und_NTA(){
    return ((config.sensor_liste.at(4)->getPin()) && (config.sensor_liste.at(2)->getPin()));
}
bool Kein_Knopf() {
    return (!(config.sensor_liste.at(3)->getPin())
    		&& !(config.sensor_liste.at(2)->getPin())
			&& !(config.sensor_liste.at(4)->getPin())
			&& !(config.sensor_liste.at(6)->getPin()));
}
bool Keine_Eingabe(){
    return (!get_X() && (!(config.sensor_liste.at(3)->getPin())
    		&& !(config.sensor_liste.at(4)->getPin())
			&& !(config.sensor_liste.at(6)->getPin())));
}
bool Automatik_Auf_Schliessen(){
    if(get_X()){
        Timer=0;
        return false;
    }
    if((Timer>=verzoegerung) || config.sensor_liste.at(3)->getPin()){
    return true;
    }
    return false;
}

void Motoren_aus(){
    config.aktor_liste.at(0)->setPin(0);
    config.aktor_liste.at(1)->setPin(0);
}
void Nichts(){}
void Tuer_auf(){
    config.aktor_liste.at(0)->setPin(1);
    config.aktor_liste.at(1)->setPin(0);
}
void Tuer_zu() {
    config.aktor_liste.at(0)->setPin(0);
    config.aktor_liste.at(1)->setPin(1);
}
void enter_Auto_Auf(){
    Timer = 0;
    Motoren_aus();
}
void Aktoren_aus(){
    config.aktor_liste.at(2)->setPin(0);
    Motoren_aus();

}
