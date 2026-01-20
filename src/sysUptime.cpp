#include "sysUptime.h"
#include <fstream>

double SysUptime::GetRawUptime() {
    double uptime = 0.0;
    std::ifstream file("/proc/uptime");

    if(file.is_open()){
        file>>uptime;
    }
    return uptime;
}

std::string SysUptime::GetFormattedUptime(){
    // Get the raw data by calling our other function
    double raw = GetRawUptime();
    long totalSec = (long)raw;

    int day = totalSec / 86400;
    int hour = (totalSec % 86400) / 3600;
    int minute = (totalSec % 3600) / 60;
    int sec = totalSec % 60;

    return std::to_string(day) + "d " + std::to_string(hour) + "h " + 
           std::to_string(minute) + "m " + std::to_string(sec) + "s";
}
