//
// Created by Ibrahim Said on 5/23/2019.
//

#include "RelayModule.h"

RelayModule::RelayModule(int pin) : _pin(pin) {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize RelayModule, could not initialise wiringPi : %s", strerror(errno));
    else
        LOG_F(INFO, "Initializing RelayModule with pin %d", pin);
    pinMode(_pin, OUTPUT);
}

void RelayModule::turnOn() {
    digitalWrite(_pin, LOW);
    LOG_F(INFO, "RelayModule connected To Pin %d Turned ON", _pin);
}


void RelayModule::turnOff() {
    digitalWrite(_pin, HIGH);
    LOG_F(INFO, "RelayModule connected To Pin %d Turned OFF successfully", _pin);
}