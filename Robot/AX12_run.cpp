#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <wiringPi.h>
#include "dynamixel_sdk.h"

#include "components/AX12.h"
#include "components/kangaroo.h"
#include "components/LCD.h"
#include "components/serialport.h"

using namespace std;

int main() {
    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    AX12 ax1(1, portHandler, packetHandler);
    AX12 ax2(2, portHandler, packetHandler);
    ax1.setMode(joint);
    ax2.setMode(joint);
    int pos1 = 500;
    int pos2 = 1000;
    ax1.goToPosition(pos1);
    ax2.goToPosition(pos2);
    while (true){
        cout<<"ax1 : "<<ax1.getPosition()<<endl;
        cout<<"ax2 : "<<ax2.getPosition()<<endl;
    }
//    ax3.goToPosition(pos3);
//    while ((abs(ax3.getPosition()-pos1)>5)){
//        cout<<"waiting"<<endl;
//    }
//    ax1.goToPosition(pos1);
//    ax2.goToPosition(pos2);




}