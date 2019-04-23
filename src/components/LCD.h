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

        void reset();
        void clear();
        void toggleCursor(bool enable = true);
        void toggleBacklight(bool enable = true);
        void printToScreen(string s,int row = 1,int offset = 0);
        void printToScreenCentered(string s,int row = 1);
};
