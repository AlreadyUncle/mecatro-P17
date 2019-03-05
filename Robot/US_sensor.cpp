/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   US_sensor.cpp
 * Author: Come
 * 
 * Created on 29 janvier 2019, 16:09
 */

#include "US_sensor.h"

using namespace std;

US_sensor::US_sensor() {      
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

int US_sensor::waitforpin(int pin, int level, int timeout){
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

int US_sensor::wait(int useconds){
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

int US_sensor::getDistance(bool verbose){
        /* trigger reading */

        digitalWrite(TRIGGER_PIN, HIGH);
        wait(10); /* wait 10 microseconds */
        digitalWrite(TRIGGER_PIN, LOW);

        if (waitforpin(ECHO_PIN, HIGH, 10000)> 0){ /* 10 ms timeout */
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
            }
        }
        else
        {
            /* sensor not firing code */
            cout << "sensor didn't fire\n" << endl;
        }
}

US_sensor::~US_sensor() {
}

