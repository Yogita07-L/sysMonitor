#include <iostream>
#include <iomanip>
#include <unistd.h>  // Essential for sleep() on Linux

#include "sysUptime.h"
#include "genInfo.h"
#include "processor.h"
#include "memory.h"

int main() {
    std::cout << "--- PROGRAM STARTING ---" << std::endl;

    sysUptime monitor; // Create the object
    genInfo m2;
    processor m3;
    memory m4;

    while(true) {
        // Clear screen logic
        std::cout << "\033[2J\033[1;1H"; 

        std::cout << "************************************" << std::endl;
        std::cout << "        LINUX SYSTEM MONITOR        " << std::endl;
        std::cout << "************************************" << std::endl;
        std::cout << "Host Name: " << m2.GetHostName() << "                 Kernel: " << m2.GetOSName() << std::endl;
        std::cout << "\nUptime " << monitor.GetFormattedUptime() << std::endl;

        float cpuUsage = m3.getUtilization();
        std::cout << "CPU Usage     " << m3.getProgressBar(cpuUsage) << " "
                   << std::fixed << std::setprecision(2) << cpuUsage << " %"<< std::endl;

        memory::MemData mem = m4.getMemData();
        std::cout << "Memory Usage  " << m3.getProgressBar(float(mem.percentage))<< " "
                    << mem.percentage << " %"<< " (" << mem.usedGB << " GB / " << mem.totalGB << " GB)" << std::endl;     

        
        sleep(1); // Wait 1 second
    }

    return 0; // Standard way to end main
}