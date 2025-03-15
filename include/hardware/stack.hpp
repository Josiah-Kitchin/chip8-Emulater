
#pragma once 

#include <stack> 
#include <cinttypes> 

namespace Hardware 
{

class MemoryStack 
/* Stack implementation for the chip8
 * Seperate from Memory for simplicity 
 */ 
{ 
  public: 
    void push_address(uint16_t address);
    uint16_t pop_address();

  private: 
    std::stack<uint16_t> m_mem_stack; 
};

}