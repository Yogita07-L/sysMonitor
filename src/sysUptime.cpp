#include "sysUptime.h"
#include <fstream>
#include"iomanip"

double sysUptime::GetRawUptime() {
    double uptime = 0.0;
    std::ifstream file("/proc/uptime");
  
    if(file.is_open()){
        file>>uptime;
    }
    return uptime;
}

std::string sysUptime::GetFormattedUptime(){
    // Get the raw data by calling our other function
    double raw = GetRawUptime();
    long totalSec = (long)raw;

    int day = totalSec / 86400;
    int hour = (totalSec % 86400) / 3600;
    int minute = (totalSec % 3600) / 60;
    int sec = totalSec % 60;

    std::stringstream uptime;
    uptime  << std::setw(2) << std::setfill('0') << day << "d " << std::setw(2) << std::setfill('0') << hour << "h " 
            << std::setw(2) << std::setfill('0') << minute << "m " << std::setw(2) << std::setfill('0')  << sec << "s ";

    return uptime.str();
}
