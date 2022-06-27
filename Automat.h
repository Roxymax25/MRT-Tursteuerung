//
// Created by Jonas on 15.06.2022.
//

#ifndef CODE_AUTOMAT_H
#define CODE_AUTOMAT_H
#include<iostream>
#include<list>
#include "Transition.h"
#include "Zustaende.h"

using namespace std;



class Automat {

private:
    const Zustaende* derzeitigerZustand;
    const std::list<Transition*> Transitionstabelle;
    bool first;

public:
    Automat(Zustaende& StartZustand, const std::list<Transition*> Transitionstabelle);

    void run();
    void restart();
    void setZustand(Zustaende Z);
    string getZustand();


};


#endif //CODE_AUTOMAT_H
