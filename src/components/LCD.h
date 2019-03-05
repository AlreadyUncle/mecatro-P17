/* 
 * File:   LCD.h
 * Author: Come
 *
 * Created on 15 janvier 2019, 17:27
 */

#ifndef LCD_H
#define LCD_H

#include <wiringPi.h>
#include <lcd.h>
#include <iostream>

//USE WIRINGPI PIN NUMBERS
#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D4  23               //Data pin 4
#define LCD_D5  22               //Data pin 5
#define LCD_D6  21               //Data pin 6
#define LCD_D7  14               //Data pin 7

using namespace std;
class LCD {
public:
    LCD();
    LCD(const LCD& orig);
    virtual ~LCD();
    
    string print_to_screen(string s,int x=0,int y=0,bool verbose=false);
    string print_to_screen_centered(string s,int line=0,bool verbose=false);
    void clear_screen();
    
    string print_score(int score,bool verbose=false);
private:
        int lcd_handle;

};

#endif /* LCD_H */

