
#include "utils.hpp"
#include <sstream> 
#include <iostream> 

void print_hex(uint16_t instruction_bytes)
{
    std::ostringstream ss; 
    ss << std::hex << instruction_bytes; 
    std::string result = ss.str(); 
    std::cout << "Instruction bytes: " << result << std::endl;
}