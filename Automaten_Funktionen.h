//
// Created by Jonas on 20.06.2022.
//

#ifndef DOORCONTROL_CPP_AUTOMATEN_FUNKTIONEN_H
#define DOORCONTROL_CPP_AUTOMATEN_FUNKTIONEN_H

#include "Konfiguration.h"
#include "Transition.h"
#include "Zustaende.h"

void set_config(Konfiguration Konfig);
void update_Timer(unsigned int delay);

bool ELG_und_NTA();
bool nur_NTZ();
bool nur_NTA();
bool nur_ELG();
bool ELG_und_NTZ();
bool nur_ELO();
bool ELO_und_NTZ();
bool ELO_und_NTA();
bool get_X();
bool Kein_Knopf();
bool Keine_Eingabe();
bool nur_X();
bool ELG_und_X_und_NTZ();
bool ELO_und_X_und_NTZ();
bool ELG_und_X();
bool ELO_und_X();
bool X_und_NTZ();
bool Automatik_Auf_Schliessen();

void Motoren_aus();
void Nichts();
void Tuer_auf();
void Tuer_zu();
void Aktoren_aus();
void enter_Auto_Auf();

#endif //DOORCONTROL_CPP_AUTOMATEN_FUNKTIONEN_H
