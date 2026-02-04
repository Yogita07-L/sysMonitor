#include "memory.h"

#include<fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

memory::MemData memory::getMemData(){
    MemData data = {0, 0};  /* Imtitalized the mem struct to 0*/
    uint64_t total;
    uint64_t available;

    std::ifstream file("/proc/meminfo"); /*Open the stat file*/

    if(file.is_open()){
        std::string line, buffer;
        while (std::getline(file, line))
        {
            /* Read the whole first line*/
            std::stringstream ss(line);
            ss >> buffer;
            if(buffer == "MemTotal:"){
                ss >> total;
            }
            if(buffer == "MemAvailable:"){
                ss >> available;
            }
            data = {total, available};
        }
    }
    else{
        /* Error if the file does not open*/
        std::cerr << "The file cannot be opened."<< std::endl;
    }
    data.totalGB = convertToGB(data.total);
    data.usedGB = convertToGB(data.total - data.available);
    data.percentage = ((float)(data.total - data.available) / data.total) * 100.0;
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