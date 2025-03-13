

#include "cpu.hpp"
#include <gtest/gtest.h> 


TEST(cpu, fetch)
{
    // Test the fetching of an instruction from memory
    Memory mem; 
    CPU cpu(mem);

    mem.write(mem.PROGRAM_START_ADDRESS, 0b11110000);
    mem.write(mem.PROGRAM_START_ADDRESS + 1, 0b00001111);

    uint16_t instruction_bytes = cpu.fetch();  
    ASSERT_EQ(0xF00F, instruction_bytes);
}

TEST(cpu, decode_values)
{
    Memory mem; 
    CPU cpu(mem);

    Instruction i = cpu.decode(0x1432);
    ASSERT_EQ(0x432, i.nnn);

    i = cpu.decode(0x7F83);
    ASSERT_EQ(i.x, 0xF);
    ASSERT_EQ(i.nn, 0x83);
    ASSERT_EQ(i.y, 0x8);
    ASSERT_EQ(i.n, 0x3);
}


TEST(cpu, decode_opcode)
{
    // Opcode tests
    Memory mem; 
    CPU cpu(mem);

    Instruction i = cpu.decode(0x00E0);
    ASSERT_EQ(i.op, Opcode::CLEAR);

    i = cpu.decode(0x00EE);
    ASSERT_EQ(i.op, Opcode::RET);

    i = cpu.decode(0x1111); 
    ASSERT_EQ(i.op, Opcode::JUMP);

    i = cpu.decode(0x2111);
    ASSERT_EQ(i.op, Opcode::CALL);

    i = cpu.decode(0x3111);
    ASSERT_EQ(i.op, Opcode::SKIP_EQUAL_VALUE);

    i = cpu.decode(0x4111);
    ASSERT_EQ(i.op, Opcode::SKIP_NOT_EQUAL_VALUE);

    i = cpu.decode(0x5110);
    ASSERT_EQ(i.op, Opcode::SKIP_EQUAL);

    i = cpu.decode(0x6000);
    ASSERT_EQ(i.op, Opcode::MOVE_VALUE);

    i = cpu.decode(0x7000);
    ASSERT_EQ(i.op, Opcode::ADD_VALUE);

    i = cpu.decode(0x8000); 
    ASSERT_EQ(i.op, Opcode::MOVE);

    i = cpu.decode(0x8001); 
    ASSERT_EQ(i.op, Opcode::OR);

    i = cpu.decode(0x8002); 
    ASSERT_EQ(i.op, Opcode::AND);

    i = cpu.decode(0x8003); 
    ASSERT_EQ(i.op, Opcode::XOR);

    i = cpu.decode(0x8004); 
    ASSERT_EQ(i.op, Opcode::ADD);

    i = cpu.decode(0x8005); 
    ASSERT_EQ(i.op, Opcode::SUB);

    i = cpu.decode(0x8006);
    ASSERT_EQ(i.op, Opcode::SHR);

    i = cpu.decode(0x8007);
    ASSERT_EQ(i.op, Opcode::SUBN);

    i = cpu.decode(0x800E);
    ASSERT_EQ(i.op, Opcode::SHL);

    i = cpu.decode(0x9000);
    ASSERT_EQ(i.op, Opcode::SKIP_NOT_EQUAL);

    i = cpu.decode(0xA000);
    ASSERT_EQ(i.op, Opcode::SET_MEM);

    i = cpu.decode(0xB000);
    ASSERT_EQ(i.op, Opcode::JUMP_PLUS);

    i = cpu.decode(0xC000);
    ASSERT_EQ(i.op, Opcode::RANDOM);

    i = cpu.decode(0xD000);
    ASSERT_EQ(i.op, Opcode::DISPLAY);

    i = cpu.decode(0xE19E);
    ASSERT_EQ(i.op, Opcode::SKIP_PRESSED);

    i = cpu.decode(0xE1A1); 
    ASSERT_EQ(i.op, Opcode::SKIP_NOT_PRESSED);

    i = cpu.decode(0xF107);
    ASSERT_EQ(i.op, Opcode::MOVE_DELAY_TIMER);

    i = cpu.decode(0xF10A);
    ASSERT_EQ(i.op, Opcode::WAIT_FOR_PRESS);

    i = cpu.decode(0xF115);
    ASSERT_EQ(i.op, Opcode::SET_DELAY_TIMER);

    i = cpu.decode(0xF118);
    ASSERT_EQ(i.op, Opcode::SET_SOUND_TIMER);

    i = cpu.decode(0xF11E);
    ASSERT_EQ(i.op, Opcode::ADD_SET_I);

    i = cpu.decode(0xF129); 
    ASSERT_EQ(i.op, Opcode::SET_I_SPRITE);

    i = cpu.decode(0xF133);
    ASSERT_EQ(i.op, Opcode::STORE_BCD);

    i = cpu.decode(0xF155);
    ASSERT_EQ(i.op, Opcode::STORE_REG_THROUGH);

    i = cpu.decode(0xF165);
    ASSERT_EQ(i.op, Opcode::READ_REG_THROUGH);
}

