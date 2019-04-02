/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   US_sensor.h
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

#define TRIGGER_PIN 23
#define ECHO_PIN    24

#define TIMEOUT 999 /* any value other than LOW or HIGH */

class US_sensor {
public:
    US_sensor();
    int getDistance(bool verbose=false);
    virtual ~US_sensor();
private:
       int waitforpin(int pin, int level, int timeout);
       int wait(int useconds);

};

#endif /* US_SENSOR_H */

