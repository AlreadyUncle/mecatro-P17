#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "components/Kangaroo.h"


using namespace std;

int main() {

    bool kangarooOperational;
    Kangaroo robot("/dev/ttyUSB0");

    kangarooOperational = robot.isOperational();

    robot.startStraightMove(4000, 100); // 4000 units ~1m
    //todo : ajouter les unités de conversions

    while (true)
        cout << "getp : " << robot.getPosition() << endl;

}
