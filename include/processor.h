#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <cstdint>

class processor
{
private:
    /* variables to store prev snapshot data     */
    uint64_t prev_total_time = 0;
    uint64_t prev_idle_time = 0;

    /*  struct to hold the cpu data     */
    struct CpuData
    {
        uint64_t idle;
        uint64_t total;
    };
    /* Private helper function to get the cpu data from snapshot */
    CpuData getSnapshot();
public:
    /* Default constructor to call the /stat file for previous time snapshot */
    processor();
    ~processor();
    /* Function to calculate the  total utilized CPU time */
    float getUtilization();
};

#endif