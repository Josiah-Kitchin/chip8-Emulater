

#include "clock.hpp"
#include <iostream>



int main() 
{ 
    constexpr int instructions_per_sec = 700; 
    Clock clock(instructions_per_sec); 

    while (true)
    {
        clock.wait_for_cycle(); 
        std::cout << "Hello world!" << std::endl;
    }
}
