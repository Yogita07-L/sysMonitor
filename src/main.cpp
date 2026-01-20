#include <iostream>
#include <unistd.h>  // Essential for sleep() on Linux
#include "sysUptime.h"

int main() {
    SysUptime monitor; // Create the object

    while(true) {
        // Clear screen logic
        std::cout << "\033[2J\033[1;1H"; 

        std::cout << "--------------------------" << std::endl;
        std::cout << "    SYSTEM MONITOR        " << std::endl;
        std::cout << "--------------------------" << std::endl;
        
        // Output the formatted string
        std::cout << "Uptime: " << monitor.GetFormattedUptime() << std::endl;
        
        sleep(1); // Wait 1 second
    }

    return 0; // Standard way to end main
}