#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <wiringPi.h>
#include "loguru.hpp"
#include "components/Jack.h"
#include "components/Ventouse.h"
#include "components/Barillet.h"

#define waitingTime 1000
using namespace std;

int main() {


    wiringPiSetup();

    Jack jack;
    Ventouse ventouse(5);
    Barillet barillet(4);

    jack.waitToRemove();
    ventouse.turnOn();
    delay(waitingTime);
    ventouse.turnOff();
    barillet.turnOn();
    delay(waitingTime);
    barillet.turnOff();

    return 0;
}