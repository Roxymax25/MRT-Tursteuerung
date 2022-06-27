/* -*- mode: c++; -*-

 * Praktikum MRT2 
 * ART1 Türsteuerung
 * Institut für Automatisierungstechnik
 * letztes Update Mai 2018
 * Autor: M.Herhold
 * Version: r3
*/

#ifndef DOORCONTROL_HH
#define DOORCONTROL_HH

#include "ncurses.h"
#include "DoorInterface.h"
#include "Digital_Input_Output.h"
#include "Automat.h"
#include "Zustaende.h"
#include "Transition.h"
#include "Sensoren.h"
#include "Aktoren.h"
#include "Konfiguration.h"
#include <vector>
#include <iostream>
#include <map>



class DoorControl {
public:
	DoorControl();
	~DoorControl();
    void run();

private:
    unsigned char port0 = 0;
    unsigned char port1 = 0;
    unsigned char port2 = 0;

    DoorInterface HUD;

    Automat* Hand;
    Automat* Automatik;
    Automat* Rep;

    Konfiguration config;

    void Handbetrieb_einrichten();
    void Automatikbetrieb_einrichten();
    void Reperaturbetrieb_einrichten();
    void Sensor_update();
    void Aktor_update();

    std::list<Transition*>Transitionstabelle_Hand;
    std::list<Transition*>Transitionstabelle_Automatik;
    std::list<Transition*>Transitionstabelle_Rep;
    std::map<std::string, Zustaende*> Handzustaende;
    std::map<std::string, Zustaende*> Automatikzustaende;
    std::map<std::string, Zustaende*> Repzustaende;






};


#endif // DOORCONTROL_HH
