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

    static void changePinA();
    static void changePinB();

    static int pinA,pinB;
    static int globalBarrelCounter;
    static bool pinASet,pinBSet;
};


#endif //MECATRO_P17_ENCODER_H
