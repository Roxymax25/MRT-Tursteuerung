//
// Created by Jonas on 17.06.2022.
//

#include "Konfiguration.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Konfiguration::Konfiguration() : sensor_liste(16), aktor_liste(8) {}


void Konfiguration::Konfiguration_einlesen() {

    for (int i = 0; i < 8 ; ++i) {
        aktor_liste.at(i) = new Aktoren(0);
    }

bool Mode;
std::string datei("Konfig.txt");
std::ifstream input(datei);
std::string Zeile;
std::string gefunden ("true");

    for (int k = 1; k < 9; ++k) {
        Mode = false;
        std::getline(input, Zeile);
        if (Zeile.find(gefunden) != std::string::npos ) {Mode = true;} //std::cout << "true in: " << k << "\n";}
        sensor_liste.at(k-1) = new Sensoren(0,Mode);

    }
    for (int j = 9; j < 17; ++j) {
        Mode = false;
        std::getline(input, Zeile);
        if (Zeile.find(gefunden) != std::string::npos ) {Mode = true;} // std::cout << "true in: " << j << "\n";}
        sensor_liste.at(j-1) = new Sensoren(0,Mode);
    }

}
