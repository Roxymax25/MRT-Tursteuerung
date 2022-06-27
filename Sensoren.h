//
// Created by Jonas on 15.06.2022.
//

#ifndef CODE_SENSOREN_H
#define CODE_SENSOREN_H
#include "Digital_Input_Output.h"


    class Sensoren{
public:

    Sensoren(bool pin, bool Mode); //Mode=0=false, High-Aktiv; Mode=1=true, Low-Aktiv
    virtual ~Sensoren();
    void setMode(bool new_Mode);
    bool getPin();
    void setPin(bool pin);
private:
    bool Mode;
    bool Pin;
 };



#endif //CODE_SENSOREN_H

