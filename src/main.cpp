

#include "clock.hpp"
#include <iostream>
#include "cpu.hpp"
#include "display.hpp"
#include "load_instructions.hpp"
#include <fstream> 
#include <SFML/Graphics.hpp>
#include "display_sfml.hpp"

void usage(int argc)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./chip <program_name>\n";
        std::exit(EXIT_FAILURE);
    }
}


int main(int argc, char** argv) 
{ 
    usage(argc);

    /*------------- HARDWARE SETUP -----------*/
    constexpr int instructions_per_sec = 700;
    Clock clock(instructions_per_sec); 
    Memory mem; 
    load_instructions(argv[1], mem);
    Display display; 
    CPU cpu(mem, display);
    /*----------------------------------------*/

    /*---------------WINDOW SETUP-------------*/
    constexpr float cell_size = 10.0f; 
    sf::RenderWindow window(sf::VideoMode(display.horizontal_pixels * 10, display.vertical_pixels * 10), "Chip8");
    /*----------------------------------------*/
       while (window.isOpen()) 
    {

        /* ---------- INSTRUCTION CYCLE -------- */
        uint16_t instruction_bytes = cpu.fetch();
        Instruction instr = cpu.decode(instruction_bytes);
        cpu.execute(instr); 
        /* ------------------------------------- */

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        display_to_sfml_window(window, display, cell_size);

        window.display(); 
        clock.wait_for_cycle(); 
    }
    return 0; 
}
