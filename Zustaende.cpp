//
// Created by Jonas on 15.06.2022.
//

#include "Zustaende.h"

Zustaende::Zustaende(Ausgabe enterFunc, Ausgabe stayFunc, Ausgabe exitFunc, const std::string Name):
enterFunc(enterFunc), stayFunc(stayFunc), exitFunc(exitFunc), Zustand(Name){}
const std::string Zustaende::getName() {
    return Zustand;
}
