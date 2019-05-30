//
// Created by Alexandre Thomas on 2019-05-30.
//

#include "JackBigRobot.h"

int JackBigRobot::jackPin  = 6;
bool JackBigRobot::closed  = true;

JackBigRobot::JackBigRobot() {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize JackBigRobot, could not initialise wiringPi : %s", strerror(errno));
    wiringPiISR (jackPin, INT_EDGE_RISING, &JackBigRobot::launch);
    LOG_F(INFO, "Succeeded to initialise JackPin %d", jackPin);
}

void JackBigRobot::launch() {
    if(closed)
    {
        closed = false;
        LOG_F(INFO, "Jack connected To Pin %d successfully removed! \n", jackPin);
    }
}

void JackBigRobot::waitToRemove() {
    if(closed){
        waitForInterrupt(jackPin,-1);
    }
    else{
        LOG_F(ERROR, "Jack connected To Pin %s is already removed!", strerror(errno));
    }
}