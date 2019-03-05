/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Come
 *
 * Created on 29 janvier 2019, 18:18
 */

#include <cstdlib>
#include "US_sensor.h"
#include "LCD.h"

using namespace std;

int main(int argc, char** argv) {
    if (wiringPiSetupGpio () == -1)
        cout << "Can't initialise wiringPi: " << strerror(errno) << endl;
     LCD* lc = new LCD();
     US_sensor* sens = new US_sensor();
     int i=0;
     while(1){
         delay(1000);
         int d = sens->getDistance();
         lc->print_score(d);
     }
}

