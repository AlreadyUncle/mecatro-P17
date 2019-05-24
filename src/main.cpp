#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <wiringPi.h>
#include "loguru.hpp"
#include "components/Jack.h"
#include "components/RelayModule.h"

#define waitingTime 1000
using namespace std;

int main() {


    wiringPiSetup();

    Jack jack;
    RelayModule ventouse(5);

    jack.waitToRemove();
    ventouse.turnOn();
    delay(waitingTime);
    ventouse.turnOff();
    delay(waitingTime);

    return 0;
}