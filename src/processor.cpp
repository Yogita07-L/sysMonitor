#include"processor.h"
#include<fstream>
#include <iostream>
#include <sstream>
 

/**
 * Default constructor to call the /stat file for previous time snapshot
 */
processor::processor(){
    CpuData prev = getSnapshot(); /* calling the function to get the prev snapshot values */

    prev_idle_time = prev.idle;   
    prev_total_time = prev.total;
}

 /**
  * Default destructor
  */
processor::~processor()
{
}

/**
 * Function for getting the current values from /proc/stat file
 */
processor::CpuData processor::getSnapshot(){
    CpuData current = {0, 0};  /* Imtitalized the current struct to 0*/

    std::ifstream file("/proc/stat"); /*Open the stat file*/
    std::string cpu_label;
    uint64_t time = 0, idle = 0, total = 0;

    if(file.is_open()){
        std::string line;
        std::getline(file, line); /* Read the whole first line*/
        std::stringstream ss(line);
        ss >> cpu_label;
        for(int i = 0; i < 10; i++){ 
            ss >> time;
            if(i == 3){   // idle time 
                idle = time;
            }
            total += time;  /* total time of current snapshot */
        }

        
        current = {idle, total};
    }
    else{
        /* Error if the file does not open*/
        std::cerr << "The file cannot be opened."<< std::endl;
    }
    return current;
}

/**
 * Function to calculate the  total utilized CPU time
 */

float processor::getUtilization(){
    CpuData current = getSnapshot();  /* Getting new data*/
    uint64_t totalDelta, idleDelta;
    float percentage;

    /* Calculating the delta for both times*/
    totalDelta = current.total - prev_total_time;
    idleDelta  = current.idle - prev_idle_time;

    // std::cout << "New: " << current.total << " Old: " << prev_total_time << std::endl; - debug
    if(totalDelta == 0) return 0.0;
    percentage = (1.0 - (static_cast<float>(idleDelta)) / totalDelta) * 100;

    prev_idle_time = current.idle; /* Updating the previous value for next snapshot calculation */
    prev_total_time = current.total;

    return percentage;
    
}

/**
 * Helper function to print the progress bar
 */
std::string processor::getProgressBar(float percentage){
    // TEMP DEBUG LINE:
    //std::cout << "DEBUG: Function received " << percentage << std::endl;
    
    if (percentage > 100.0f) percentage = 100.0f;
    if (percentage < 0.0f) percentage = 0.0f;
    /*Calculate the slots full from 50 slots of the bar*/
    float bars_float = (percentage / 100.0) * 50.0; 

    /*To round the nearest whole number*/
    int bars = static_cast<int>(bars_float + 0.5); 

    int spaces = 50 - bars;
    std::string bar =  "[" ;
    
    for (int itr = 0; itr < bars; itr++)
    {
        bar +=  "|";
    }
    for (int itr = 0; itr < spaces; itr++)
    {
        bar +=  "-";
    }
    return bar + "]";
}