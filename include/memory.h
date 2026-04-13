#ifndef MEMORY_H
#define MEMORY_H

#include"cstdint"

class memory
{
private:
    /* Helper function to convert memory from kBs to GBs*/
    float convertToGB(float memKb);
    
public:
    /*  struct to hold the memory data     */
    struct MemData {
        uint64_t total = 0;
        uint64_t available = 0;
        double totalGB = 0.0;
        double usedGB = 0.0;
        double percentage = 0.0;

        // New members
        uint64_t swapTotalKB = 0;
        uint64_t swapFreeKB = 0;
        double swapTotalGB = 0.0;
        double swapUsedGB = 0.0;
        double swapPercentage = 0.0;
    };

    /* To get the total used memory */
    float getMemUsage();
    
    /* Helper function to get the memory data from /proc/meminfo */
    MemData getMemData();
};
















#endif