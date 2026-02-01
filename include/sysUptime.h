#ifndef SYSUPTIME_H
#define SYSUPTIME_H

#include <string>

class sysUptime {
public:
    // Get the pure number from Linux
    double GetRawUptime();

    // Transform that number into a clock format
    std::string GetFormattedUptime();
};

#endif