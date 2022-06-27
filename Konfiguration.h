//
// Created by Jonas on 17.06.2022.
//

#ifndef TUERSTEUERUNG_KONFIGURATION_H
#define TUERSTEUERUNG_KONFIGURATION_H
#include "Digital_Input_Output.h"
#include "Sensoren.h"
#include "Aktoren.h"
#include <vector>



class Konfiguration {


public:
    Konfiguration();
    void Konfiguration_einlesen();
    // std::vector<Aktoren*> get_aktor_liste();
    // std::vector<Sensoren*> get_sensor_liste();
    std::vector<Aktoren*> aktor_liste;
    std::vector<Sensoren*> sensor_liste;


private:

};


#endif //TUERSTEUERUNG_KONFIGURATION_H
