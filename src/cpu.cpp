
#include "cpu.hpp"

CPU::CPU(Memory &mem)
    : m_program_counter(mem.PROGRAM_START_ADDRESS), m_mem_location(0), m_memory(mem)
{
    std::fill(m_general_registers.begin(), m_general_registers.end(), 0);
}

/* ---- Getters and setters ---- */

void CPU::set_register(std::size_t reg_num, uint8_t value) { m_general_registers[reg_num] = value; }

uint8_t CPU::get_register(std::size_t reg_num) { return m_general_registers[reg_num]; }

/* ---- Instruction Cycle ---- */

uint16_t CPU::fetch()
/* Reads two bytes at pc and combines them to get the
 * instruction
 * Increments pc by 2
 */
{
    uint8_t byte1 = m_memory.read(m_program_counter);
    uint8_t byte2 = m_memory.read(m_program_counter + 1);
    m_program_counter += 2;

    uint16_t instruction_bytes = (byte1 << 8) | byte2;
    return instruction_bytes;
}







Instruction CPU::decode(uint16_t instruction_bytes)
/* Converts instruction_bytes into an Instruction */
{
    Instruction instruction; 
    // First nibble dictates what kind of instruction it is 
    uint8_t opcode_byte = instruction_bytes >> 12;

    // Second nibble, used to look up one of 16 registers
    instruction.x = (instruction_bytes & (0xF << 8)) >> 8; 

    // Third nibble, used to look up one of 16 registers
    instruction.y = (instruction_bytes & (0xF << 4)) >> 4;

    // Fourth nibble, a 4 bit number
    instruction.n = instruction_bytes & 0xF;

    // Second byte, an 8 bit immediate number
    instruction.nn = instruction_bytes & 0xFF; 

    // Second, third and fourth nibbles. 12 bit immediate memory address
    instruction.nnn = instruction_bytes & 0xFFF; 

    instruction.op = Opcode::INVALID_OP; 
    
    switch (opcode_byte)
    {
        case(0x0): 
        {
            if (instruction.nnn == 0x0E0)
                instruction.op = Opcode::CLEAR; 
            if (instruction.nnn == 0x0EE)
                instruction.op = Opcode::RET; 
            break;     
        }
        case (0x1):
            instruction.op = Opcode::JUMP;
            break; 
        case (0x2): 
            instruction.op = Opcode::CALL; 
            break; 
        case (0x3): 
            instruction.op = Opcode::SKIP_EQUAL_VALUE; 
            break; 
        case (0x4): 
            instruction.op = Opcode::SKIP_NOT_EQUAL_VALUE; 
            break; 
        case (0x5): 
            instruction.op = Opcode::SKIP_EQUAL; 
            break; 
        case (0x6): 
            instruction.op = Opcode::MOVE_VALUE; 
            break; 
        case (0x7): 
            instruction.op = Opcode::ADD_VALUE; 
            break; 
        case (0x8): 
        {
            switch (instruction.n)
            {
                case (0x0): 
                    instruction.op = Opcode::MOVE; 
                    break; 
                case (0x1): 
                    instruction.op = Opcode::OR; 
                    break; 
                case (0x2): 
                    instruction.op = Opcode::AND; 
                    break; 
                case (0x3): 
                    instruction.op = Opcode::XOR; 
                    break; 
                case (0x4): 
                    instruction.op = Opcode::ADD; 
                    break; 
                case (0x5): 
                    instruction.op = Opcode::SUB; 
                    break; 
                case (0x6): 
                    instruction.op = Opcode::SHR; 
                    break; 
                case (0x7): 
                    instruction.op = Opcode::SUBN; 
                    break; 
                case (0xE): 
                    instruction.op = Opcode::SHL; 
                    break;
            }
            break; 
        } 
        case (0x9): 
            instruction.op = Opcode::SKIP_NOT_EQUAL; 
            break; 
        case (0xA): 
            instruction.op = Opcode::SET_MEM; 
            break; 
        case (0xB): 
            instruction.op = Opcode::JUMP_PLUS; 
            break; 
        case (0xC): 
            instruction.op = Opcode::RANDOM; 
            break; 
        case (0xD): 
            instruction.op = Opcode::DISPLAY;
            break; 
        case (0xE): 
        {
            if (instruction.n == 0xE) 
                instruction.op = Opcode::SKIP_PRESSED; 
            else if (instruction.n == 0x1)
                instruction.op = Opcode::SKIP_NOT_PRESSED; 
            break; 
        }
        case (0xF): 
        {
            switch (instruction.nn)
            {
                case (0x07): 
                    instruction.op = Opcode::MOVE_DELAY_TIMER; 
                    break; 
                case (0x0A): 
                    instruction.op = Opcode::WAIT_FOR_PRESS; 
                    break; 
                case (0x15): 
                    instruction.op = Opcode::SET_DELAY_TIMER; 
                    break; 
                case (0x18): 
                    instruction.op = Opcode::SET_SOUND_TIMER; 
                    break; 
                case (0x1E): 
                    instruction.op = Opcode::ADD_SET_I;
                    break; 
                case (0x29): 
                    instruction.op = Opcode::SET_I_SPRITE; 
                    break; 
                case (0x33): 
                    instruction.op = Opcode::STORE_BCD; 
                    break;
                case (0x55): 
                    instruction.op = Opcode::STORE_REG_THROUGH; 
                    break; 
                case(0x65): 
                    instruction.op = Opcode::READ_REG_THROUGH; 
                    break; 
            }
        }
    }

    return instruction; 

}
