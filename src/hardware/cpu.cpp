
#include "hardware/cpu.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <cstdlib> 

using namespace Hardware;

CPU::CPU(Bus &bus)
    : m_program_counter(bus.memory.PROGRAM_START_ADDRESS), m_mem_location(0), m_bus(bus),

      // Functions for different opcodes, can be written here or in another execute_ function
      m_opcode_table{

          {Opcode::INVALID_OP, [this](const Instruction &instr) { execute_invalid(instr); }},

          {Opcode::DISPLAY, [this](const Instruction &instr) { execute_draw_sprite(instr); }},

          {Opcode::CLEAR, [this](const Instruction &instr) { m_bus.display.clear(); }},

          {Opcode::JUMP, [this](const Instruction &instr) { m_program_counter = instr.nnn; }},

          {Opcode::MOVE_VALUE, [this](const Instruction &instr) { m_general_registers[instr.x] = instr.nn; }},

          {Opcode::ADD_VALUE, [this](const Instruction &instr) { m_general_registers[instr.x] += instr.nn; }},

          {Opcode::SET_MEM, [this](const Instruction &instr) { m_mem_location = instr.nnn; }},

          {Opcode::CALL, [this](const Instruction &instr)
          {
                m_bus.stack.push_address(m_program_counter);
                m_program_counter = instr.nnn;
          }},

          {Opcode::RET, [this](const Instruction& instr) 
          {
                uint16_t return_address = m_bus.stack.pop_address(); 
                m_program_counter = return_address; 
          }},

          {Opcode::SKIP_EQUAL_VALUE, [this](const Instruction& instr)
          {
                uint8_t register_value = m_general_registers[instr.x];
                if (register_value == instr.nn)
                    m_program_counter += 2; 
          }}, 

          {Opcode::SKIP_NOT_EQUAL_VALUE, [this](const Instruction& instr)
          {
                uint8_t register_value = m_general_registers[instr.x];
                if (register_value != instr.nn)
                    m_program_counter += 2; 
          }}, 

          {Opcode::SKIP_EQUAL, [this](const Instruction& instr)
          {
                uint8_t value_x  = m_general_registers[instr.x];
                uint8_t value_y  = m_general_registers[instr.y];
                if (value_x == value_y)
                    m_program_counter += 2; 
          }}, 

          {Opcode::SKIP_NOT_EQUAL, [this](const Instruction& instr)
          {
                uint8_t value_x  = m_general_registers[instr.x];
                uint8_t value_y  = m_general_registers[instr.y];
                if (value_x != value_y)
                    m_program_counter += 2; 
          }}, 

          {Opcode::MOVE, [this](const Instruction &instr) { m_general_registers[instr.x] = m_general_registers[instr.y]; }},

          {Opcode::OR, [this](const Instruction &instr) { m_general_registers[instr.x] |= m_general_registers[instr.y]; }},

          {Opcode::AND, [this](const Instruction &instr) { m_general_registers[instr.x] &= m_general_registers[instr.y]; }},

          {Opcode::XOR, [this](const Instruction &instr) { m_general_registers[instr.x] ^= m_general_registers[instr.y]; }},

          {Opcode::ADD, [this](const Instruction &instr) 
          { 
                uint8_t x_value = m_general_registers[instr.x]; 
                uint8_t y_value = m_general_registers[instr.y]; 
                if (uint16_t(x_value) + uint16_t(y_value) > 255) //Set flag for overflow
                    m_flag = 1; 
                else
                    m_flag = 0; 
                m_general_registers[instr.x] += y_value; 
          }},

          {Opcode::SUB, [this](const Instruction &instr) 
          { 
                uint8_t x_value = m_general_registers[instr.x]; 
                uint8_t y_value = m_general_registers[instr.y]; 
                if (x_value > y_value) //Set flag for overflow
                    m_flag = 1; 
                else
                    m_flag = 0; 
                m_general_registers[instr.x] -= y_value; 
          }},

          {Opcode::SUBN, [this](const Instruction &instr) 
          { 
                uint8_t x_value = m_general_registers[instr.x]; 
                uint8_t y_value = m_general_registers[instr.y]; 
                if (y_value > x_value) //Set flag for overflow
                    m_flag = 1; 
                else
                    m_flag = 0; 
                m_general_registers[instr.y] -= x_value; 
          }},

          {Opcode::SHR, [this](const Instruction &instr) 
          { 
                uint8_t value = m_general_registers[instr.x];
                uint8_t shifted_bit = value & 0b1;
                if (shifted_bit)
                    m_flag = 1; 
                else
                    m_flag = 0; 
                m_general_registers[instr.x] >> 1; 
          }},

          {Opcode::SHR, [this](const Instruction &instr) 
          { 
                uint8_t value = m_general_registers[instr.x];
                uint8_t shifted_bit = value >> 7;
                if (shifted_bit)
                    m_flag = 1; 
                else
                    m_flag = 0; 
                m_general_registers[instr.x] << 1; 
          }},

          {Opcode::JUMP_PLUS, [this](const Instruction &instr) { m_program_counter = instr.nnn + m_general_registers[0]; }},

          {Opcode::RANDOM, [this](const Instruction &instr) 
          { 
                uint8_t random = rand() % (instr.nn + 1); 
                m_general_registers[instr.x] &= random;
          }},

          {Opcode::SKIP_PRESSED, [this](const Instruction &instr) 
          { 
                uint8_t key = m_general_registers[instr.x];
                if (m_bus.keypad.is_pressed(key))
                    m_program_counter += 2; 
          }},

          {Opcode::SKIP_NOT_PRESSED, [this](const Instruction &instr) 
          { 
                uint8_t key = m_general_registers[instr.x];
                if (!m_bus.keypad.is_pressed(key))
                    m_program_counter += 2; 
          }},

          {Opcode::ADD_SET_I, [this](const Instruction &instr) 
          { 
                uint8_t value = m_general_registers[instr.x];
                if (uint16_t(value) + m_mem_location >= 0x1000)
                    m_flag = 1;
                m_mem_location += value; 
          }},


      }

{

    std::fill(m_general_registers.begin(), m_general_registers.end(), 0);
}

uint16_t CPU::fetch()
/* Reads two bytes at pc and combines them to get the
 * instruction
 * Increments pc by 2
 *
 * Terminates the program with success if the program counter goes past the memory size
 */
{
    if (m_program_counter >= m_bus.memory.SIZE)
    {
        std::exit(EXIT_SUCCESS);
    }
    uint8_t byte1 = m_bus.memory.read(m_program_counter);
    uint8_t byte2 = m_bus.memory.read(m_program_counter + 1);
    m_program_counter += 2;

    uint16_t instruction_bytes = (byte1 << 8) | byte2;

    return instruction_bytes;
}

void CPU::execute(Instruction instr)
{
    auto execute_function = m_opcode_table.at(instr.op);
    execute_function(instr);
}

/* ---------------------- EXECUTE METHODS ------------------------- */

void CPU::execute_invalid(const Instruction &instr)
{
    std::cerr << "INVALID INSTRUCTION\n";
    std::exit(EXIT_FAILURE);
}

void CPU::execute_draw_sprite(const Instruction &instr)
/*
    Instruction to draw sprite data onto the screen
    - Takes the y and x coordinate from registers and a sprite height value
    - Reads sprite_height bytes from mem location register
    - For each bit == 1 in that byte, if the pixel on that screen is white, make it black
    - Otherwise, make it white (with y coord is current sprite height and x coordinate is
   current bit)

    If a pixel is changed to black, the flag register is set to 1

*/
{
    uint8_t sprite_height = instr.n;

    m_flag = 0;

    uint8_t y_coord = m_general_registers[instr.y] % m_bus.display.vertical_pixels;
    uint8_t x_coord = m_general_registers[instr.x] % m_bus.display.horizontal_pixels;

    for (uint8_t sprite_offset = 0; sprite_offset < sprite_height; sprite_offset++)
    {
        // Read the sprite row (1 byte)
        uint8_t sprite_byte = m_bus.memory.read(m_mem_location + sprite_offset);

        // Stop if at the bottom of the screen
        size_t pixel_y_position = y_coord + sprite_offset;
        if (pixel_y_position >= m_bus.display.vertical_pixels)
            break;

        for (int bit_num = 0; bit_num < 8; bit_num++)
        {
            size_t pixel_x_position = x_coord + bit_num;
            // If it is at the right edge of the screen, go to the next row
            if (pixel_x_position >= m_bus.display.horizontal_pixels)
                break;

            // Each pixel is a bit, start from most significant
            uint8_t pixel_bit = (sprite_byte >> (7 - bit_num)) & 0b1;
            if (pixel_bit && m_bus.display.is_white(pixel_x_position, pixel_y_position))
            {
                m_bus.display.write_color(pixel_x_position, pixel_y_position,
                                          Display::Color::BLACK);
                m_flag = 1;
            }
            else if (pixel_bit && m_bus.display.is_black(pixel_x_position, pixel_y_position))
            {
                m_bus.display.write_color(pixel_x_position, pixel_y_position,
                                          Display::Color::WHITE);
            }
        }
    }
}

/* ------------------- DECODE SWITCH STATEMENT --------------------------*/

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
    case (0x0):
        if (instruction.nnn == 0x0E0)
            instruction.op = Opcode::CLEAR;
        if (instruction.nnn == 0x0EE)
            instruction.op = Opcode::RET;
        break;
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
        if (instruction.n == 0xE)
            instruction.op = Opcode::SKIP_PRESSED;
        else if (instruction.n == 0x1)
            instruction.op = Opcode::SKIP_NOT_PRESSED;
        break;
    case (0xF):
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
        case (0x65):
            instruction.op = Opcode::READ_REG_THROUGH;
            break;
        }
    }

    return instruction;
}
