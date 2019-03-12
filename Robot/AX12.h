//
// Created by 魏士清 on 2019-01-22.
//

#ifndef MECATRO_P17_AX12_H
#define MECATRO_P17_AX12_H

#if defined(__linux__) || defined(__APPLE__)
#include <fcntl.h>
#include <termios.h>
#define STDIN_FILENO 0
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "libs/dxl_sdk_cpp_source/include/dynamixel_sdk/dynamixel_sdk.h"

// Control table address
#define ADDR_MX_TORQUE_ENABLE           24                  // Control table address is different in Dynamixel model
#define ADDR_MX_GOAL_POSITION           30
#define ADDR_MX_PRESENT_POSITION        36
#define ADDR_MX_CW_ANGLE_LIMIT          6
#define ADDR_MX_CCW_ANGLE_LIMIT         8
#define ADDR_MX_MOVING_SPEED            32
#define ADDR_MX_PRESENT_SPEED           38


// Protocol version
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel

// Default setting
//#define DXL_ID                          1                   // Dynamixel ID: 1
#define BAUDRATE                        1000000
#define DEVICENAME                      "/dev/ttyACM0"      // Check which port is being used on your controller
// ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      10                 // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      1000               // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MOVING_STATUS_THRESHOLD     5                  // Dynamixel moving status threshold

#define ESC_ASCII_VALUE                 0x1b
enum AX12Mode { joint, wheel };







class AX12 {
public:
    AX12(int,dynamixel::PortHandler *,dynamixel::PacketHandler *);
    int ID;
    AX12Mode mode;
    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;
    static int test;
    void goToPosition(int);
    void setSpeed(int);
    void setMode(AX12Mode);
    int getPosition();
    

};



#endif //MECATRO_P17_AX12_H
