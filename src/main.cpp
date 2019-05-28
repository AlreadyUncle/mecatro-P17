#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <wiringPi.h>
#include "loguru.hpp"

#include "components/Kangaroo.h"

using namespace std;

int main() {


    wiringPiSetup();


    Kangaroo kangaroo("/dev/ttyUSB0");

    kangaroo.startTurnMove(10000, 4000);

    while (true) {
        cout << kangaroo.getRawPosition() << endl;
    }


    return 0;
}