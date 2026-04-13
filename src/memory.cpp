#include "memory.h"

#include<fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

memory::MemData memory::getMemData(){
    MemData data = {};  /* Imtitalized the mem struct to 0*/


    std::ifstream file("/proc/meminfo"); /*Open the stat file*/

    if(file.is_open()){
        std::string line, buffer;
        while (std::getline(file, line))
        {
            /* Read the whole first line*/
            std::stringstream ss(line);
            ss >> buffer;
            if(buffer == "MemTotal:"){
                ss >> data.total;
            }
            if(buffer == "MemAvailable:"){
                ss >> data.available;
            }
            if(buffer == "SwapTotal:"){
                ss >> data.swapTotalKB;
            }
            if(buffer == "SwapFree:"){
                ss >> data.swapFreeKB;
            }           
        }
    }
    else{
        /* Error if the file does not open*/
        std::cerr << "The file cannot be opened."<< std::endl;
    }
    data.totalGB    = convertToGB(data.total);
    data.usedGB     = convertToGB(data.total - data.available);
    data.percentage = ((float)(data.total - data.available) / data.total) * 100.0;

    data.swapTotalGB    = convertToGB(data.swapTotalKB);
    data.swapUsedGB     = convertToGB(data.swapTotalKB - data.swapFreeKB);

    if (data.swapTotalGB > 0) {
        data.swapPercentage = (data.swapUsedGB / data.swapTotalGB) * 100;
    } 
    else {
        data.swapPercentage = 0.0;
    }

    return data;
}

/**
 * To get the total used memory 
 */ 

float memory::getMemUsage(){
    return getMemData().percentage;
}

/* Helper function to convert memory from kBs to GBs*/
float memory::convertToGB(float memKb){
    float convert;
    convert = memKb / (1024.0 * 1024.0 );
    return convert;
}