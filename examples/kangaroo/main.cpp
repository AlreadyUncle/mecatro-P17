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
    etat=robot.getport();
    if(etat==true)
    {
        cout<<"Succes"<<endl;
        //Correction : 1) Initialiser d'abord ; 2 ) Start ce que l'on desire
        robot.init();
        cout<<robot.avancer(10,500,cm)<<endl;
        cout<<robot.tourner(500,360)<<endl;

    }
    else
    {
        cout<<"Erreur"<<endl;
    }

}
