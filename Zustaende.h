//
// Created by Jonas on 15.06.2022.
//

#ifndef CODE_ZUSTAENDE_H
#define CODE_ZUSTAENDE_H
#include <string>

typedef void (*Ausgabe)();

class Zustaende {
public:
Ausgabe enterFunc, stayFunc, exitFunc;
const std::string Zustand;
Zustaende(Ausgabe enterFunc,Ausgabe stayFunc,Ausgabe exitFunc, const std::string Name);
const std::string getName();
};

#endif //CODE_ZUSTAENDE_H


