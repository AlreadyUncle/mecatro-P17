#include <iostream>
#include "components/kangaroo.h"
#include "components/serialport.h"
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

int main()
{
    
    bool etat;
    Ckangaroo robot("/dev/serial0");
    etat=robot.isOperationnal();
    if(etat==true)
    {
        cout<<"Operationnal"<<endl;
        while(true){
            for(int speed=4000;speed<7501;speed+=500){
                cout<<robot.turnB(360,speed,true)<<endl;
                cout<<robot.turnB(-360,speed,true)<<endl;
            }
        }

    }
    else
    {
        cout<<"Connection error"<<endl;
    }

}
