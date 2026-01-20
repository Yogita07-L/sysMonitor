#include <iostream>
#include "sysUptime.h"

int main() {
    SysUptime monitor;
    std::cout << "Testing Uptime: " << monitor.GetUptime() << std::endl;
    return 0;
}