
#pragma once

#include <array>
#include <cstdint>

class Memory
/* Global 4KB memory for the chip8 
 * Can be read and written to at an address a byte at a time 
 * Stores constant important start addresses 
 */
{
  public:
    // Loads in neccesary data for the beggining state of memory
    Memory();

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    static constexpr uint16_t PROGRAM_START_ADDRESS = 0x200;
    static constexpr uint16_t FONT_START_ADDRESS = 0x000;

  private:
    // 4 KB of RAM
    static constexpr std::size_t SIZE = 4096;
    std::array<uint8_t, SIZE> m_data;
};
