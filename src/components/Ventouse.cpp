//
// Created by Ibrahim Said on 5/23/2019.
//

#include "Ventouse.h"

Ventouse::Ventouse(int pin) : Pin(pin){
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize Ventouse, could not initialise wiringPi : %s", strerror(errno));
    pinMode (Pin, OUTPUT) ;

}
void Ventouse::turnOn(){
    digitalWrite (Pin, LOW) ;
    LOG_F(INFO, "Ventouse connected To Pin %d Turned ON successfully  \n", Pin);
}


void Ventouse::turnOff(){
    digitalWrite (Pin, HIGH) ;
    LOG_F(INFO, "Ventouse connected To Pin %d Turned OFF successfully  \n", Pin);
}

