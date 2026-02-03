#include <iostream>
#include <unistd.h>  // Essential for sleep() on Linux
#include "sysUptime.h"
#include "genInfo.h"
#include "processor.h"

int main() {
    std::cout << "--- PROGRAM STARTING ---" << std::endl;

    sysUptime monitor; // Create the object
    genInfo m2;
    processor m3;

    while(true) {
        // Clear screen logic
        std::cout << "\033[2J\033[1;1H"; 

        std::cout << "************************************" << std::endl;
        std::cout << "        LINUX SYSTEM MONITOR        " << std::endl;
        std::cout << "************************************" << std::endl;
        std::cout << "Host Name: " << m2.GetHostName() << "                 Kernel: " << m2.GetOSName() << std::endl;
        std::cout << "\nUptime " << monitor.GetFormattedUptime() << std::endl;

        float currentUsage = m3.getUtilization();
        std::cout << "CPU Usage " << m3.getProgressBar(currentUsage) << " "
                    << currentUsage << " %"<< std::endl;
        // Output the formatted string

        
        sleep(1); // Wait 1 second
    }

    return 0; // Standard way to end main
}