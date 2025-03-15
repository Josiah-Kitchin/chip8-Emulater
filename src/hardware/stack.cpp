
#include "hardware/stack.hpp"

using namespace Hardware; 

void MemoryStack::push_address(uint16_t address)
{
    m_mem_stack.push(address);
}

uint16_t MemoryStack::pop_address()
{
    uint16_t address = m_mem_stack.top(); 
    m_mem_stack.pop(); 
    return address; 
}






