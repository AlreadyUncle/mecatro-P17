/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UltrasonicSensor.cpp
 * Author: Come
 * 
 * Created on 29 janvier 2019, 16:09
 */

#include "UltrasonicSensor.h"

using namespace std;

UltrasonicSensor::UltrasonicSensor(int trigger_pin, int echo_pin) : TRIGGER_PIN(trigger_pin), ECHO_PIN(echo_pin) {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize sensor, could not initialise wiringPi : %s", strerror(errno));
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

int UltrasonicSensor::waitForPin(int pin, int level, int timeout) {
    struct timeval now, start;
    long micros;

    gettimeofday(&start, nullptr);

    while (true) {
        gettimeofday(&now, nullptr);
        micros = now.tv_usec - start.tv_usec + 1000000 * (now.tv_sec - start.tv_sec);

        if (digitalRead(pin) == level) return micros;
        if (micros > timeout) return -1;
    }
}

int UltrasonicSensor::wait(int useconds) {
    struct timeval now, start;
    long micros;

    gettimeofday(&start, nullptr);

    while (true) {
        gettimeofday(&now, nullptr);
        micros = now.tv_usec - start.tv_usec + 1000000 * (now.tv_sec - start.tv_sec);
        if (micros > useconds) return micros;
    }
}

int UltrasonicSensor::getDistance() {
    /* trigger reading */

    digitalWrite(TRIGGER_PIN, HIGH);
    wait(10); /* wait 10 microseconds */
    digitalWrite(TRIGGER_PIN, LOW);

    if (waitForPin(ECHO_PIN, HIGH, 10000) > 0) { /* 10 ms timeout */
        //todo: ask why 60ms instead of 36ms as in the doc http://www.robot-electronics.co.uk/htm/srf04tech.htm
        int pulsewidth = waitForPin(ECHO_PIN, LOW, 60000L); /* 60 ms timeout */

        if (pulsewidth > 0) {
            double distanceMm = pulsewidth * 340 * 0.001 / 2;
            LOG_F(1, "Sensor echo at %dµs = %fmm", pulsewidth, distanceMm);
            return (int) (distanceMm);
        } else {
            /* no object detected code */
            LOG_F(1, "Sensor echo timed out, no object detected");
            return -1;
        }
    } else {
        /* sensor not firing code */
        LOG_F(ERROR, "Sensor did not fire");
        return -2;
    }
}
