#include <iostream>
#include <iomanip>
#include <unistd.h>  // Essential for sleep() on Linux

#include "sysUptime.h"
#include "genInfo.h"
#include "processor.h"
#include "memory.h"
#include "sysStats.h"

int main() {
    std::cout << "--- PROGRAM STARTING ---" << std::endl;

    sysUptime monitor; // Create the object
    genInfo m2;
    processor m3;
    memory m4;
    sysStats m5;

    while(true) {
        // Clear screen logic
        std::cout << "\033[2J\033[1;1H"; 

        std::cout << "\n************************************" << std::endl;
        std::cout << "        LINUX SYSTEM MONITOR        " << std::endl;
        std::cout << "************************************" << std::endl;

        std::cout << "\nHost Name: " << m2.GetHostName() << "                 Kernel: " << m2.GetOSName() << std::endl;
       
        sysStats::loadData data = m5.getLoadData();
        std::cout << "Uptime " << monitor.GetFormattedUptime() 
                    << "         Tasks: " << data.runningTasks << " running / " << data.totalTasks <<" total" << std::endl;

        
        std::cout << "\nLoad Average: " << data.loadAvg1 << " (1m) " << data.loadAvg5 << " (5m) " 
                    << data.loadAvg15 << " (15m)" << std::endl;


        float cpuUsage = m3.getUtilization();
        std::cout << "\nCPU Usage     " << m3.getProgressBar(cpuUsage) << " "
                   << std::fixed << std::setprecision(2) << cpuUsage << " %"<< std::endl;

        memory::MemData mem = m4.getMemData();
        std::cout << "Memory Usage  " << m3.getProgressBar(float(mem.percentage))<< " "
                    << mem.percentage << " %"<< " (" << mem.usedGB << " GB / " << mem.totalGB << " GB)" << std::endl;     

        std::cout << "Swap Usage    " << m3.getProgressBar(float(mem.swapPercentage))<< " "
                    << mem.swapPercentage << " %"<< " (" << mem.swapUsedGB << " GB / " << mem.swapTotalGB << " GB)" << std::endl;     

        
        sleep(1); // Wait 1 second
    }

    return 0; // Standard way to end main
}