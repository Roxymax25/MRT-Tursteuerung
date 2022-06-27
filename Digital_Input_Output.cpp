//
// Created by Jonas on 15.06.2022.
//

#include "Digital_Input_Output.h"
#include <iostream>

Digital_Input_Output::Digital_Input_Output(unsigned int pin) :pin(pin){}

Digital_Input_Output::~Digital_Input_Output(){
}

int Digital_Input_Output::getPin(){
    return pin;
}
void Digital_Input_Output::setPin(unsigned int Signal) {
    pin = Signal;
}
