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
    if (wiringPiSetupGpio () == -1)
        cout << "Can't initialise wiringPi: " << strerror(errno) << endl;
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

int UltrasonicSensor::waitforpin(int pin, int level, int timeout){
    struct timeval now, start;
    long micros;

    gettimeofday(&start, NULL);
    micros = 0;

    while(1){
        gettimeofday(&now, NULL);
        micros = now.tv_usec - start.tv_usec + 1000000*(now.tv_sec - start.tv_sec);

        if (digitalRead(pin) == level) return micros;
        if(micros>timeout) return -1;
    }
    return -1;
}

int UltrasonicSensor::wait(int useconds){
    struct timeval now, start;
    long micros;

    gettimeofday(&start, NULL);
    micros = 0;

    while(1){
        gettimeofday(&now, NULL);
        micros = now.tv_usec - start.tv_usec + 1000000*(now.tv_sec - start.tv_sec);
        if(micros>useconds) return micros;
    }
    return -1;
}

int UltrasonicSensor::getDistance(bool verbose){
        /* trigger reading */

        digitalWrite(TRIGGER_PIN, HIGH);
        wait(10); /* wait 10 microseconds */
        digitalWrite(TRIGGER_PIN, LOW);

        if (waitforpin(ECHO_PIN, HIGH, 10000)> 0){ /* 10 ms timeout */
            //todo: ask why 60ms instead of 36ms as in the doc http://www.robot-electronics.co.uk/htm/srf04tech.htm
            int pulsewidth = waitforpin(ECHO_PIN, LOW, 60000L); /* 60 ms timeout */

            if (pulsewidth>0)
            {
                if(verbose){
                    cout << "echo at " << pulsewidth << " micros" << endl;
                    cout << "echo at " << pulsewidth*340*0.001/2 << " mm" << endl;
                }
                return (int)(pulsewidth*340*0.001/2);
            }
            else
            {
                /* no object detected code */
                cout << "echo timed out" << endl;
                return -1;
            }
        }
        else
        {
            /* sensor not firing code */
            cout << "sensor didn't fire\n" << endl;
            return -2;
        }
}

UltrasonicSensor::~UltrasonicSensor() {
}

