//
// Created by Alexandre Thomas on 2019-05-30.
//

#ifndef MECATRO_P17_JACKBIGROBOT_H
#define MECATRO_P17_JACKBIGROBOT_H

#include <wiringPi.h>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <sys/time.h>
#include "loguru.hpp"

class JackBigRobot {
public:
    JackBigRobot();

    static void launch();

    /**
     * Blocking function that waits until the jack pin detects a change (EDGE_RISING), ie the jack cable is removed.
     */
    static void waitToRemove();

    static bool closed;
    static int jackPin;
};


#endif //MECATRO_P17_JACKBIGROBOT_H
