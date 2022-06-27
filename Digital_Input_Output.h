//
// Created by Jonas on 15.06.2022.
//

#ifndef CODE_DIGITAL_INPUT_OUTPUT_H
#define CODE_DIGITAL_INPUT_OUTPUT_H
#include <iostream>


    class Digital_Input_Output {


    public:
        Digital_Input_Output(unsigned int pin);
        virtual ~Digital_Input_Output();
        virtual int getPin();
        void setPin(unsigned int Signal);
    protected:
        int pin;
    };


#endif //CODE_Digital_Input_Output_H
