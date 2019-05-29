//
// Created by Ibrahim Said on 5/22/2019.
//

#include "Jack.h"

int Jack::jackPin  = 6;
bool Jack::closed  = true;

Jack::Jack() {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize Jack, could not initialise wiringPi : %s", strerror(errno));
    wiringPiISR (jackPin, INT_EDGE_RISING, &Jack::launch);
    LOG_F(INFO, "Succeeded to initialise JackPin %d", jackPin);
}

void Jack::launch() {
    if(closed)
    {
        closed = false;
        LOG_F(INFO, "Jack connected To Pin %d successfully removed! \n", jackPin);
    }
}

void Jack::waitToRemove() {
    if(closed){
        waitForInterrupt(jackPin,-1);
    }
    else{
        LOG_F(ERROR, "Jack connected To Pin %s is already removed!", strerror(errno));
    }
}