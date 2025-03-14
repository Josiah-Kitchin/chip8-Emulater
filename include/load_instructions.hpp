
#pragma once

#include <fstream> 
#include <string> 
#include <cstdint> 
#include <vector> 
#include <iostream> 
#include "memory.hpp"

void load_instructions(const std::string& file_name, Memory& mem);
void write_instructions(const std::string& file_name, const std::vector<uint8_t>& bytes);