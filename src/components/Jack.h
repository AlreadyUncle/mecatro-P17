//
// Created by Ibrahim Said on 5/22/2019.
//

#ifndef MECATRO_P17_JACK_H
#define MECATRO_P17_JACK_H

#include <wiringPi.h>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <sys/time.h>
#include "loguru.hpp"

class Jack {
    public:
        Jack();
        static void launch();
        static void waitToRemove();
        static bool closed;
        static int jackPin;
    };


#endif //MECATRO_P17_JACK_H
