#ifndef SYSSTATS_H
#define SYSTATS_H


#include<cstdint>

class sysStats
{
private:
    
public:
/**
 * Struct to hold the all load average data 
 */
    struct loadData
    {
        int runningTasks = 0;
        int totalTasks = 0;
        float loadAvg1 = 0.0;
        float loadAvg5 = 0.0;
        float loadAvg15 = 0.0;
    };
    
    /**
     * Fucntion to read the load average data from /proc/loadavg
     */

    loadData getLoadData();
};




#endif 

