//
// Created by Alexandre Thomas on 2019-05-25.
//

#ifndef MECATRO_P17_ENCODER_H
#define MECATRO_P17_ENCODER_H


#include <wiringPi.h>
#include <errno.h>
#include <cstring>
#include "loguru.hpp"

class Encoder {
public:
    Encoder();

    static void increaseGlobalCounter();

    static int pin;
    static int globalBarrelCounter;
};


#endif //MECATRO_P17_ENCODER_H
