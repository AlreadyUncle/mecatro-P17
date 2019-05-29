//
// Created by Ibrahim Said on 4/16/2019.
//
#ifndef MECATRO_P17_LCD_H
#define MECATRO_P17_LCD_H

#include "SerialPort.h"


class LCD {

public:
    SerialPort m_serialPortOutput;
    bool m_isOpened;

    LCD(string portName);

    void reset();

    void clear();

    void toggleCursor(bool enable = true);

    void toggleBacklight(bool enable = true);

    void printToScreen(string s, int row = 1, int offset = 0);

    void printToScreenCentered(string s, int row = 1);
};

#endif //MECATRO_LCD_H
