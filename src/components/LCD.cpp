//
// Created by Ibrahim Said on 4/16/2019.
//

#include "LCD.h"
#define ESC 27
#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 4

LCD::LCD(string portName) {
    m_isOpened=(m_serialPortOutput.open(portName.c_str(),115200)!=-1);
}

void LCD::reset(){
    char command[] = {ESC,'C','\0'};
    m_serialPortOutput.puts(command);
    usleep(1500);
}

void LCD::clear(){
    printToScreen(string(SCREEN_HEIGHT*SCREEN_WIDTH,' '));
}
void LCD::toggleCursor(bool enable){
    char command[] = {ESC,enable?'S':'s','\0'};
    m_serialPortOutput.puts(command);
}

void LCD::toggleBacklight(bool enable){
    char command[] = {ESC,enable?'B':'b','\0'};
    m_serialPortOutput.puts(command);
}

void LCD::printToScreen(string s,int row,int offset){
    row = (row-1+SCREEN_HEIGHT)%SCREEN_HEIGHT + 1;
    char command[] = {static_cast<char>(row),'\0'};
    m_serialPortOutput.puts(command);
    if(offset>=1) {
        std::string space(offset, ' ');
        s = space + s;
    }
    while(s.length()>=SCREEN_WIDTH){
        m_serialPortOutput.puts(s.substr(0,SCREEN_WIDTH).c_str());
        s = s.substr(SCREEN_WIDTH);
        if(s.length()!=0){
        command[0] = command[0]%SCREEN_HEIGHT+1;
        m_serialPortOutput.puts(command);
        }
    }
    if(s.length()!=0)
        m_serialPortOutput.puts(s.c_str());
}

void LCD::printToScreenCentered(string s,int row){
    if(s.length()>=SCREEN_WIDTH)
        printToScreen(s,row,0);
    else {
        int offset = (SCREEN_WIDTH - s.length()) / 2;
        printToScreen(s, row, offset);
    }
}


