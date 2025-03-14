

#pragma once

#include <chrono> 



class Clock
/* Represents the clock for a cpu 
 * Determines the speed of execution for instruction cycle
 */
{
  public: 
    Clock(int instructions_per_sec); 
    void wait_for_cycle(); 

  private: 
    std::chrono::milliseconds m_instruction_duration; 
};

