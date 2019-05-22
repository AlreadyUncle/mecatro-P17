/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UltrasonicSensor.h
 * Author: Come
 *
 * Created on 29 janvier 2019, 16:09
 */

#ifndef US_SENSOR_H
#define US_SENSOR_H

#include <wiringPi.h>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <sys/time.h>
#include "loguru.hpp"



class UltrasonicSensor {
public:
    /**
     * Instantiate a new sensor. Sensors may share the trigger pin, however they must have their own echo pin.
     * @param trigger_pin
     * @param echo_pin
     */
    UltrasonicSensor(int trigger_pin, int echo_pin);
    /**
     * Return distance to the next obstacle as measured by the sensor (in mm)
     * If no object was detected, return -1
     * If the sensor did not fire (therefore, the echo signal was never raised), return -2
     */
    int getDistance();

private:
       int waitForPin(int pin, int level, int timeout);
       int wait(int useconds);
       const int ECHO_PIN, TRIGGER_PIN;

};

#endif /* US_SENSOR_H */

