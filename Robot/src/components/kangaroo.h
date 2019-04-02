#ifndef KANGAROO_H
#define KANGAROO_H
#include "serialport.h"
#include <stdlib.h>

enum mode
{
    moteur1=0x31,moteur2=0x32,drive=0x44,turn=0x54
};

enum vitesse
{
    km0=0, km05=200,km1=400,km15=600,km2=800,km25=1000,km3=1200,km35=1400,km4=1600,km45=1800,km5=2000
};

class Kangaroo
{

public:
    Kangaroo();
    Kangaroo(string portName);
    ~Kangaroo();

    bool moveForward();
    bool turn();

    //todo: remove
    // B : blocking (ass a while loop to wait until movement is completed)
    // NB : non-blocking (just sends the command)
    bool forwardB(int distance, int v, bool verbose=false);
    bool forwardNB(int distance, int v);
    bool turnB (int angle,int v, bool verbose=false);
    bool turnNB (int angle,int v);
    bool isOperationnal();

    string getPosition (mode m);
    int getPositionMax (mode m, int &positionMax); // retourne le range de position maximal
    int getPositionMin (mode m , int &positionMin); //retourne le range de position minimal
    int getSpeed (mode m, int &speed); //retourne la vitesse
    char getState(mode m);


    CSerialPort m_serialPortOutput;
    bool m_isOpened;
    bool m_init;

    bool init();
    bool start(mode m);
    bool powerdown(mode m);
    void downZero();
private:
    bool putCommand(char mode,string cmd);
};

#endif // KANGAROO_H
