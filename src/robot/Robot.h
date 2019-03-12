//
// Created by Alexandre Thomas on 2019-03-05.
//

#ifndef MECATRO_P17_ROBOT_H
#define MECATRO_P17_ROBOT_H


#include "../components/AX12.h"
#include "../components/kangaroo.h"
#include "../components/US_sensor.h"

class Robot {

public:
    Robot(vector<int> ax12_id);

    // tmp, will probably change with BT
    // Kangaroo methods
    void goTo(int x, int y, int angle);
    bool isMovementFinished();

    int getX();
    int getY();
    int getAngle();

    // AX12 methods

private:
    dynamixel::PortHandler* portHandler;
    dynamixel::PacketHandler* packetHandler;

    map<int, AX12> ax_servos;
    Ckangaroo kangaroo;
    US_sensor sensor;
};


#endif //MECATRO_P17_ROBOT_H
