

#pragma once
#include "data/instruction.hpp"
#include "hardware/bus.hpp"

#include <array>
#include <cinttypes>
#include <unordered_map> 
#include <functional> 
#include <chrono> 

namespace Hardware {

class CPU
/* Incharge of fetching, decoding, and executing instructions
 * Can read and write to memory 
 */
{
  public:
    CPU(Bus& bus);

    // Instruction cycle methods
    uint16_t fetch();
    Instruction decode(uint16_t instruction_bytes);
    void execute(Instruction instr); 

    // Information to update media 
    bool is_sound_playing(); 

  private:
    // Methods for execution
    void execute_draw_sprite(const Instruction& instr);
    void execute_invalid(const Instruction& instr);

    void set_flag(uint8_t bit);

    // Registers
    std::array<uint8_t, 16> m_general_registers;

    // Special registers
    uint16_t m_program_counter;
    uint16_t m_mem_location;

    // Timer logic 
    void update_timers();
    uint8_t m_delay_timer = 0;
    uint8_t m_sound_timer = 0;
    std::chrono::steady_clock::time_point m_last_timer_update = std::chrono::steady_clock::now(); 

    Bus& m_bus; 

    // Maps opcodes to cpu execute functions 
    const std::unordered_map<Opcode, std::function<void(const Instruction&)>> m_opcode_table; 
};

}
