//
// Created by Ibrahim Said on 5/23/2019.
//

#include "Barillet.h"

Barillet::Barillet(int pin) : Pin(pin){
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize Barillet, could not initialise wiringPi : %s", strerror(errno));
    pinMode (Pin, OUTPUT) ;

}
void Barillet::turnOn(){
    digitalWrite (Pin, LOW) ;
    LOG_F(INFO, "Barillet connected To Pin %d Turned ON successfully  \n", Pin);
}


void Barillet::turnOff(){
    digitalWrite (Pin, HIGH) ;
    LOG_F(INFO, "Barillet connected To Pin %d Turned OFF successfully  \n", Pin);
}
