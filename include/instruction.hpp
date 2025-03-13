
#pragma once 
#include <cstdint> 

/* All instruction opcodes for the chip8
 */
enum class Opcode
{
    CLEAR, 
    RET,
    JUMP, 
    CALL, 
    SKIP_EQUAL_VALUE, 
    SKIP_NOT_EQUAL_VALUE, 
    SKIP_EQUAL, 
    MOVE_VALUE, 
    ADD, 
    MOVE, 
    OR, 
    AND, 
    XOR, 
    SUB, 
    SHR, 
    SUBN, 
    SHL, 
    SKIP_NOT_EQUAL,
    SET_MEM, 
    JUMP_PLUS, 
    RANDOM, 
    DISPLAY, 
    SKIP_PRESSED,
    SKIP_NOT_PRESSED, 
    MOVE_DELAY_TIMER, 
    WAIT_FOR_PRESS, 
    SET_DELAY_TIMER, 
    SET_SOUND_TIMER, 
    ADD_VALUE, 
    ADD_SET_I, 
    SET_I_SPRITE, 
    STORE_BCD, 
    STORE_REG_THROUGH, 
    READ_REG_THROUGH,

    INVALID_OP
};


struct Instruction 
{ 
    Opcode op; 
    // Register 1 nibble 
    uint8_t x; 
    // Register 2 nibble 
    uint8_t y; 
    // 4 bit value 
    uint8_t n; 
    // 1 byte value
    uint8_t nn; 
    // 12 byte value, an address 
    uint16_t nnn; 
};
