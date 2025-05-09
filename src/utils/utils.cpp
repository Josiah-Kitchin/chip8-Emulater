
#include "utils/utils.hpp"
#include <sstream> 
#include <iostream> 

void Utils::print_hex(uint16_t instruction_bytes)
{
    std::ostringstream ss; 
    ss << std::hex << instruction_bytes; 
    std::string result = ss.str(); 
    std::cout << result << std::endl;
}