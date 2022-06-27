//
// Created by Jonas on 15.06.2022.
//

#include "Transition.h"
Transition::Transition(const Zustaende& Vorher, const Zustaende& Nachher, Bedingung con)
                        :ZVorher(Vorher), ZNachher(Nachher), condition(con){}


