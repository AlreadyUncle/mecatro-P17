/* 
 * File:   LCD.cpp
 * Author: Come
 * 
 * Created on 15 janvier 2019, 17:27
 */

#include "LCD.h"

LCD::LCD() {
    lcd_handle = lcdInit (4, 20, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
    for(int i=0;i<20;i++){
        print_to_screen_centered("Mecatro",0);
        print_to_screen_centered("MinesParistech",1);
        print_to_screen_centered("Coupe de France",2);
        print_to_screen_centered("de Robotique 2k19",3);
        delay(100);
        clear_screen();
        delay(100);
    }
}

string LCD::print_to_screen(string s,int x,int y,bool verbose){
    if(verbose)
        cout << "printing to screen: " << s <<endl;
    lcdPosition(lcd_handle, x, y);
    lcdPuts(lcd_handle, s.c_str());
    return s;
}

string LCD::print_to_screen_centered(string s,int line,bool verbose){
    int offset = (20-s.length())/2;
    return print_to_screen(s,offset,line,verbose);
}

string LCD::print_score(int score,bool verbose){
    clear_screen();
    return print_to_screen_centered("Score: "+to_string(score),2,verbose);
}

void LCD::clear_screen(){lcdClear(lcd_handle);}

LCD::LCD(const LCD& orig) {
}

LCD::~LCD() {
}

