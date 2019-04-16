//
// Created by Ibrahim Said on 4/16/2019.
//

#include "LCD.h"
#define ESC 27
LCD::LCD(string portName) {
    m_isOpened=(m_serialPortOutput.open(portName.c_str(),115200)!=-1);
}

void LCD::clear_screen(){
    char command[] = {ESC,'C','\0'};
    m_serialPortOutput.puts(command);
    usleep(1500);
}

void LCD::cursor(bool enable){
    char command[] = {ESC,enable?'S':'s','\0'};
    m_serialPortOutput.puts(command);
}

void LCD::backlight(bool enable){
    char command[] = {ESC,enable?'B':'b','\0'};
    m_serialPortOutput.puts(command);
}

void LCD::print_to_screen(string s,int row,int offset){
    char command[] = {row,'\0'};
    m_serialPortOutput.puts(command);
    if(offset>=1) {
        std::string space(offset, ' ');
        s = space + s;
    }
    cout<<s<<endl;
    cout<<s.length()<<endl;
    m_serialPortOutput.puts(s.c_str());
}

LCD::~LCD() {
}

