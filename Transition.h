//
// Created by Jonas on 15.06.2022.
//

#ifndef CODE_TRANSITION_H
#define CODE_TRANSITION_H
#include "Transition.h"
#include "Zustaende.h"
#include <iostream>


typedef bool (*Bedingung) ();

class Transition {

public:

    const Zustaende& ZVorher;
    const Zustaende& ZNachher;
    Bedingung condition;
    Transition(const Zustaende& ZVorher, const Zustaende& ZNachher, Bedingung con);

};


#endif //CODE_TRANSITION_H
