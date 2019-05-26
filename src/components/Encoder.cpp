//
// Created by Alexandre Thomas on 2019-05-25.
//

#include "Encoder.h"


int Encoder::pin = 8;
int Encoder::globalBarrelCounter = 0;

Encoder::Encoder() {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize Encoder, could not initialise wiringPi : %s", strerror(errno));
    wiringPiISR(pin, INT_EDGE_RISING, &Encoder::increaseGlobalCounter);
    LOG_F(INFO, "Succeeded to initialise Encoder Pin %d", pin);

}

void Encoder::increaseGlobalCounter() {
    globalBarrelCounter++;
    //LOG_F(1, "Encoder global counter increase %d", globalBarrelCounter);
}

