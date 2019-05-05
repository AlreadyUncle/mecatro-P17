#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <wiringPi.h>
#include <wiringSerial.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "loguru.hpp"

using namespace std;

class SerialPort
{

private :
    int m_fd;

public:
    SerialPort();
    int open(const char * device, int baud);
    void close();
    bool putchar (char c);
    bool puts (const char * command);
    int dataAvailable();
    bool getchar(char *car);
    bool gets(char *reponse, unsigned int taille);
    void flush ();
    
};

#endif // SERIALPORT_H
