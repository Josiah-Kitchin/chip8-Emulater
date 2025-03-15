

#pragma once 

#include "hardware/cpu.hpp"
#include "hardware/display.hpp"
#include "hardware/keypad.hpp"
#include "hardware/memory.hpp"
#include "hardware/stack.hpp"

namespace Hardware
{
    struct Bus
    /* Stores all of the hardware components for the cpu to connect to */
    {
        Display display; 
        Keypad keypad; 
        Memory memory;
        MemoryStack stack; 
    };
}
