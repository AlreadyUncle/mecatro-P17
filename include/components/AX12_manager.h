#include <iostream>
#include <string>

#include "dynamixel_sdk.h"                                  // Uses Dynamixel SDK library

using namespace std;

#ifndef MECATRO_GITHUB_AX12_MANAGER_H
#define MECATRO_GITHUB_AX12_MANAGER_H


class AX12_manager {
public:
    // instantiate AX12 manager : instantiate params, packetHandler and portHandler
    AX12_manager(string device_name);

    // open port, set baudrate, enable torque
    int init_connection();

private:
    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;

};


#endif //MECATRO_GITHUB_AX12_MANAGER_H
