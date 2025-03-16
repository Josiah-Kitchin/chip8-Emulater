

#include "hardware/memory.hpp"
#include "data/font.hpp"

#include "utils/utils.hpp"
#include <iostream> 

using namespace Hardware; 

Memory::Memory()
/* Initalizes memory with 4 KB, loads data that needs to be in memory
 */
{
    m_data.fill(0);

    // Fill the start with font data
    for (size_t i = 0; i < Font::DATA.size(); i++)
        write(Memory::FONT_START_ADDRESS + i, Font::DATA[i]);
}

uint8_t Memory::read(uint16_t address) 
{ 
    return m_data[address]; 
}

void Memory::write(uint16_t address, uint8_t value) { m_data[address] = value; }




