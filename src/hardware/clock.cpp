

#include "hardware/clock.hpp"
#include <chrono> 
#include <thread> 

using namespace std::chrono; 
using Hardware::Clock; 

Clock::Clock(int instructions_per_sec)
{
    m_instruction_duration = milliseconds(1000 / instructions_per_sec);
}

void Clock::wait_for_cycle()
{
    std::this_thread::sleep_for(m_instruction_duration);
}



