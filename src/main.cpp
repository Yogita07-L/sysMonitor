#include <iostream>
#include <unistd.h>  // Essential for sleep() on Linux
#include "sysUptime.h"
#include "genInfo.h"

int main() {
    SysUptime monitor; // Create the object
    GenInfo m2;

    while(true) {
        // Clear screen logic
        std::cout << "\033[2J\033[1;1H"; 

        std::cout << "--------------------------" << std::endl;
        std::cout << "    SYSTEM MONITOR        " << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "Host Name: " << m2.GetHostName() << "                 Kernel: " << m2.GetOSName() << std::endl;
        
        std::cout << "Uptime " << monitor.GetFormattedUptime() << std::endl;
        
        // Output the formatted string

        
        sleep(1); // Wait 1 second
    }

    return 0; // Standard way to end main
}