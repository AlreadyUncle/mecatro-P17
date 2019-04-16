#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>
#include "components/LCD.h"
#include "components/kangaroo.h"

int main() {
    LCD screen("/dev/ttyUSB0");

    if(screen.m_isOpened) {
        screen.clear_screen();
        screen.print_to_screen("Mecatro", 3, 5);
        //cout<<"done"<<endl;
    }
    return 0;
}