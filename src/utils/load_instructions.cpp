
#include "utils/load_instructions.hpp"

void Utils::load_instructions(const std::string& file_name, Hardware::Memory& mem)
/* 
    Load the binary instructions of a file into memory
*/
{
    std::ifstream file(file_name, std::ios::binary);
    if (!file)
    {
        std::cerr << "No program \"" << file_name << "\" found\n";
        std::exit(EXIT_FAILURE);
    }

    uint16_t current_address = mem.PROGRAM_START_ADDRESS; 

    uint8_t byte; 
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) 
    {
        mem.write(current_address, byte);
        current_address++; 
    }
    file.close(); 
}


void Utils::write_instructions(const std::string& file_name, const std::vector<uint8_t>& bytes)
/*
    For debugging, write binary to a file 
*/
{
    std::ofstream program(file_name, std::ios::binary); 
    if (!program)
    {
        std::cerr << "Could not write program\n";
        std::exit(EXIT_FAILURE);
    }
    for (uint8_t byte : bytes)
    {
        program.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }
    program.close(); 
}