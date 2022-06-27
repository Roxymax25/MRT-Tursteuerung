//
// Created by Jonas on 15.06.2022.
//

#include "Automat.h"



Automat::Automat(Zustaende& StartZustand, std::list<Transition*> Transitionstabelle):
derzeitigerZustand(&StartZustand), Transitionstabelle(Transitionstabelle), first(true)
{}
void Automat::restart() {
    first = true;
}

string Automat::getZustand() {
    return derzeitigerZustand->Zustand;
}
void Automat::setZustand(Zustaende Z){
    derzeitigerZustand = &Z;
}

void Automat::run(){

    if (first){
        derzeitigerZustand->enterFunc(); first = false;}

    for(std::list<Transition*>::const_iterator i = Transitionstabelle.begin(); i!= Transitionstabelle.end();i++){
        Transition *t = *(i);
        if (&t->ZVorher == derzeitigerZustand) {

            if (t->condition()){
                derzeitigerZustand->exitFunc();
                derzeitigerZustand = &t->ZNachher;
                derzeitigerZustand->enterFunc();
                return;
            }
        }
    }
    derzeitigerZustand->stayFunc();


}
