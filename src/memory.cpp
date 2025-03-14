

#include "memory.hpp"
#include "font.hpp"

Memory::Memory()
/* Initalizes memory with 4 KB, loads data that needs to be in memory
 */
{
    m_data.fill(0);

    // Fill the start with font data
    for (uint8_t byte : Font::DATA)
        write(Memory::FONT_START_ADDRESS, byte);
}

uint8_t Memory::read(uint16_t address) { return m_data.at(address); }

void Memory::write(uint16_t address, uint8_t value) { m_data.at(address) = value; }




