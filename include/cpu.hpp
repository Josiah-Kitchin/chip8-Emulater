

#pragma once
#include "instruction.hpp"
#include "memory.hpp"
#include "display.hpp"
#include <array>
#include <cinttypes>
#include <unordered_map> 
#include <functional> 


class CPU
/* Incharge of fetching, decoding, and executing instructions
 * Can read and write to memory 
 */
{
  public:
    CPU(Memory& mem, Display& display);

    // Instruction cycle methods
    uint16_t fetch();
    Instruction decode(uint16_t instruction_bytes);
    void execute(Instruction instr); 

  private:
    // Methods for execution
    void execute_draw_sprite(const Instruction& instr);
    void execute_invalid(const Instruction& instr);


    // Registers
    std::array<uint8_t, 16> m_general_registers;
    void set_register(std::size_t reg_num, uint8_t value);
    uint8_t get_register(std::size_t reg_num);

    // Special registers
    uint16_t m_program_counter;
    uint16_t m_mem_location;
    uint8_t m_delay_timer;
    uint8_t m_flag; 
    uint8_t m_sound_timer;

    // Hardware connections
    Memory& m_memory;
    Display& m_display; 

    // Maps opcodes to cpu execute functions 
    const std::unordered_map<Opcode, std::function<void(const Instruction&)>> m_opcode_table; 
};

