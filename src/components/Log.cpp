//
// Created by 魏士清 on 2019-03-05.
//
#include "Log.h"


string Log::log_Name ="Log_File_" + Log::get_time() + ".txt";

void Log::write_log(string text)
{
    std::ofstream log_file(log_Name, std::ios_base::out | std::ios_base::app );
    log_file << get_time() + " " + text << std::endl;
}

string Log::get_time()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",timeinfo);
    return string (buffer);
}



