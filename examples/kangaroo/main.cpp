#include <iostream>
#include "kangaroo.h"
#include "serialport.h"
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
        cout<<robot.forwardB(10,500,cm)<<endl;
        cout<<robot.turnB(500,360)<<endl;

    }
    else
    {
        cout<<"Connection rrror"<<endl;
    }

}
