
#pragma once

#include <fstream> 
#include <string> 
#include <cstdint> 
#include <vector> 
#include <iostream> 
#include "hardware/memory.hpp"


namespace Utils
{

// Loads instructions from file_name into memory
void load_instructions(const std::string& file_name, Hardware::Memory& mem);
// For testing, writes a vector of bytes into a binary file 
void write_instructions(const std::string& file_name, const std::vector<uint8_t>& bytes);

}