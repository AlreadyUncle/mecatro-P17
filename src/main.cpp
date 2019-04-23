#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>
#include "components/LCD.h"
#include "components/kangaroo.h"

int main() {
    LCD screen("/dev/ttyUSB0");

    if(screen.m_isOpened) {
        screen.reset();
        screen.toggleCursor(false);
        for(int i=0;i<20;i++){
            screen.printToScreenCentered("Mecatro",1);
            screen.printToScreenCentered("MinesParistech",2);
            screen.printToScreenCentered("Coupe de France",3);
            screen.printToScreenCentered("de Robotique 2k19",4);
            delay(1000);
            screen.clear();
            delay(100);
        }
    }
    return 0;
}