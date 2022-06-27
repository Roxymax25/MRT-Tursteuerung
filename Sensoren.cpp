//
// Created by Jonas on 15.06.2022.
//

#include "Sensoren.h"

Sensoren::Sensoren(bool pin, bool Mode) : Pin(pin) ,Mode(Mode){}
Sensoren::~Sensoren() {}

bool Sensoren::getPin() {
    return Pin;
}
void Sensoren::setMode(bool new_Mode) {
    Mode = new_Mode;
}

void Sensoren::setPin(bool pin)
{
	if(Mode){
		Pin=!pin;
	} else {
		Pin=pin;
	}
}
