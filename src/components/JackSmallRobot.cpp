//
// Created by Ibrahim Said on 5/22/2019.
//

#include "JackSmallRobot.h"

int JackSmallRobot::jackPin  = 6;
bool JackSmallRobot::closed  = true;

JackSmallRobot::JackSmallRobot() {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize Jack, could not initialise wiringPi : %s", strerror(errno));
    wiringPiISR (jackPin, INT_EDGE_RISING, &JackSmallRobot::launch);
    LOG_F(INFO, "Succeeded to initialise JackPin %d", jackPin);
}

void JackSmallRobot::launch() {
    if(closed)
    {
        closed = false;
        LOG_F(INFO, "Jack connected To Pin %d successfully removed! \n", jackPin);
    }
}

void JackSmallRobot::waitToRemove() {
    if(closed){
        waitForInterrupt(jackPin,-1);
    }
    else{
        LOG_F(ERROR, "Jack connected To Pin %s is already removed!", strerror(errno));
    }
}