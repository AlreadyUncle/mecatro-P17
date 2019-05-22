//
// Created by Ibrahim Said on 5/22/2019.
//

#include "Jack.h"


Jack::Jack(int pin) {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize Jack, could not initialise wiringPi : %s", strerror(errno));
    jackPin = pin;
    closed = true;
    //todo find a way to initialize pin inside the function
    // wiringPiISR (jackPin, INT_EDGE_RISING, &Jack::launch);
    LOG_F(INFO, "Succeeded to initialise JackPin\n", jackPin);
}

void Jack::launch() {
    if(closed)
    {
        closed = false;
        LOG_F(INFO, "Jack connected To Pin %d successfully removed! \n", jackPin);
    }
}

void Jack::wait() {
    if(closed){
        waitForInterrupt(jackPin,-1);
    }
    else{
        LOG_F(ERROR, "Jack connected To Pin %d is already removed!", strerror(errno));
    }
}