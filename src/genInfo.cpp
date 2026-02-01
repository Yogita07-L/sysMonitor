#include "genInfo.h"
#include <fstream>


std::string genInfo::GetHostName(){

    std::string hostname;
    std::ifstream file("/proc/sys/kernel/hostname");

    if(file.is_open()){
        file >> hostname;
    }
    return hostname;
}

std::string genInfo::GetOSName(){
    std::string Kernel;
    std::ifstream file("/proc/version");

    if(file.is_open()){
        file >> Kernel;
        file >> Kernel;
        file >> Kernel;
    }
    return Kernel;
}