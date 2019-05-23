//
// Created by Ibrahim Said on 5/23/2019.
//

#ifndef MECATRO_P17_VENTOUSE_H
#define MECATRO_P17_VENTOUSE_H

#include <wiringPi.h>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <sys/time.h>
#include "loguru.hpp"

class Ventouse {

public:

    Ventouse(int pin);

    void turnOn();

    void turnOff();


private:
    const int Pin;

};


#endif //MECATRO_P17_VENTOUSE_H
