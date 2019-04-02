//
// Created by Alexandre Thomas on 2019-03-05.
//

#include "Robot.h"

#define PORT_NAME_KANGAROO              "/dev/serial0"      // Port address for Kangaroo
#define PORT_NAME_DXL                   "/dev/ttyACM0"      // Port adress for dynamixel devices
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel



void Robot::goTo(int x, int y, int angle) {

}


int Robot::getX() {
    return 0;
}

int Robot::getY() {
    return 0;
}

int Robot::getAngle() {
    return 0;
}

Robot::Robot(vector<int> ax12_id) {
    // initialize all devices
    portHandler = dynamixel::PortHandler::getPortHandler(PORT_NAME_DXL);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    for (int id : ax12_id) {
        ax_servos[id] = AX12(id, portHandler, packetHandler);
    }

    kangaroo = Ckangaroo(PORT_NAME_KANGAROO);
    sensor = US_sensor();
}

