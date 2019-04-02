/* 
 * File:   main.cpp
 * Author: Come
 *
 * Created on 29 janvier 2019, 18:18
 */

#include <cstdlib>
#include <iostream>
#include "US_sensor.h"
#include "LCD.h"
#include "AX12.h"
#include "kangaroo.h"
#include "serialport.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <wiringPi.h>
#include <wiringSerial.h>
#include "libs/dxl_sdk_cpp_source/include/dynamixel_sdk/dynamixel_sdk.h"

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    if (wiringPiSetupGpio () == -1)
        cout << "Can't initialise wiringPi: " << strerror(errno) << endl;
    LCD* lc = new LCD();
    US_sensor* sens = new US_sensor();
    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    AX12 ax1(1, portHandler, packetHandler);
    AX12 ax2(2, portHandler, packetHandler);
    ax1.setMode(joint);
    ax2.setMode(joint);
    int i=0;
    struct timeval now, start;
    bool etat;
    Ckangaroo robot("/dev/serial0");
    etat=robot.isOperationnal();
    if(etat==true)
    {
        cout<<"Operationnal"<<endl;
        while(true){ 
            int randompos=0;
            int dist=sens->getDistance();
            //robot.start(drive);
            do{
                randompos=(rand())%1024;
                ax1.goToPosition(randompos);
                ax2.goToPosition(randompos);
                cout << robot.forwardNB(10+(dist-300)/2,3*min(dist-250,500),true) <<endl;
                delay(1000);
                dist=sens->getDistance();
                lc->print_to_screen_centered("Dist="+to_string(dist),1);
                cout<<"dist"<<dist<<endl;
            }while(dist>300);
            cout<< robot.turnB(180,2000,true)<<endl;
        }
        /*while(true){
            lc->print_to_screen_centered("Dist="+to_string(sens->getDistance()),1);
        }*/
    }
    else
    {
        cout<<"Connection error"<<endl;
    }
}

