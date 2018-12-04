#include <iostream>
#include "kangaroo.h"
#include "serialport.h"
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

int main()
{
    
    bool etat;
    bool pas;
    Ckangaroo robot("/dev/serial0");
    etat=robot.getport();
    if(etat==true)
    {
        cout<<"Succes"<<endl;
        //Correction : 1) Initialiser d'abord ; 2 ) Start ce que l'on desire
        pas=robot.allerEn(500,100,cm);
        cout<<pas<<endl;

    }
    else
    {
        cout<<"Erreur"<<endl;
    }

}
