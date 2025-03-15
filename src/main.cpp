

#include <iostream>
#include <fstream> 
#include <SFML/Graphics.hpp>

#include "hardware/hardware.hpp"
#include "media/sfml.hpp"
#include "utils/load_instructions.hpp"

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
    Hardware::Clock clock(instructions_per_sec); 

    // Stores hardware components
    Hardware::Bus bus; 
    Utils::load_instructions(argv[1], bus.memory);
    Hardware::CPU cpu(bus);
    /*----------------------------------------*/

    /*---------------WINDOW SETUP-------------*/
    constexpr float cell_size = 10.0f; 
    sf::RenderWindow window(sf::VideoMode(bus.display.horizontal_pixels * 10, bus.display.vertical_pixels * 10), "Chip8");
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

            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
                Media::handle_sfml_keypad(event, bus.keypad);
        }

        Media::display_to_sfml_window(window, bus.display, cell_size);

        window.display(); 
        clock.wait_for_cycle(); 
    }
    return 0; 
}
