//
// Created by Alexandre Thomas on 2019-03-05.
//

#ifndef MECATRO_P17_ROBOT_H
#define MECATRO_P17_ROBOT_H


#include "../components/AX12.h"
#include "../components/kangaroo.h"
#include "../components/US_sensor.h"
#include "../components/serialport.h"
#include "../components/LCD.h"


#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <wiringPi.h>
#include <wiringSerial.h>

class Robot {

public:
    Robot(int n_ax12);

    // tmp, will probably change with BT
    // Kangaroo methods
    void goForwardTo(int x, int y, int speed, int angle, bool verbose=false);
    void turnTo(int x, int y, int speed, int angle, bool verbose=false);
    void stop(bool verbose=false);
    bool isMovementFinished(bool verbose=false);

    int getX(bool verbose=false);
    int getY(bool verbose=false);
    int getAngle(bool verbose=false);

    // AX12 methods

private:
    dynamixel::PortHandler* m_portHandler;
    dynamixel::PacketHandler* m_packetHandler;

    AX12 m_ax_servos[];
    Kangaroo m_kangaroo;
    US_sensor m_sensor;
    LCD m_screen;
    
    int m_X,m_Y;
    int m_angle;
};


#endif //MECATRO_P17_ROBOT_H
