//
// Created by Jonas on 15.06.2022.
//

#ifndef CODE_AKTOREN_H
#define CODE_AKTOREN_H
#include "Digital_Input_Output.h"

    class Aktoren  : public Digital_Input_Output{
    public:
        Aktoren(unsigned int pin);
        virtual ~Aktoren();

    };



#endif //CODE_AKTOREN_H
