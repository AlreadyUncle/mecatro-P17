//
// Created by 魏士清 on 2019-03-05.
//

#ifndef MECATRO_P17_LOG_H
#define MECATRO_P17_LOG_H

#include <stdio.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;
class Log{
public:
    static string log_Name;
public:
    static void write_log(string text);
    static string get_time();


};


#endif //MECATRO_P17_LOG_H
