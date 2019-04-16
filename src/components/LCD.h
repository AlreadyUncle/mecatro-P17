//
// Created by Ibrahim Said on 4/16/2019.
//

#include "serialport.h"


class LCD {

    public:
        CSerialPort m_serialPortOutput;
        bool m_isOpened;

        LCD(string portName);
        ~LCD();
/*
        string print_to_screen(string s,int x=0,int y=0,bool verbose=false);
        string print_to_screen_centered(string s,int line=0,bool verbose=false);
*/
        void clear_screen();
        void cursor(bool enable = true);
        void backlight(bool enable = true);
        void print_to_screen(string s,int row = 1,int offset = 0);
};
