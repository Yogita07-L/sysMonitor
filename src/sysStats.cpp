#include "sysStats.h"

#include<fstream>
#include<iostream>
#include<sstream>

/**
 * Fucntion to read the load average data from /proc/loadavg
 */
sysStats::loadData sysStats::getLoadData(){
    sysStats::loadData data = {};
    std::ifstream file("/proc/loadavg");

    if(file.is_open())
    {
        std::string line, taskBuffer;
        std::getline(file, line);
        std::stringstream ss(line);
        char slash;

        ss >> data.loadAvg1;
        ss >> data.loadAvg5;
        ss >> data.loadAvg15;
        ss >> taskBuffer;

        std::stringstream stream(taskBuffer);
        stream >> data.runningTasks;

        stream >> slash;

        stream >> data.totalTasks;

        
    }
    else
    {
        /* Error if the file does not open*/
        std::cerr << "The file cannot be opened."<< std::endl;
    }
    return data;
    
}
