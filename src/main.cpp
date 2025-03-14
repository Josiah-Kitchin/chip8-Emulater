

#include "clock.hpp"
#include <iostream>
#include "cpu.hpp"
#include "display.hpp"
#include "load_instructions.hpp"
#include <fstream> 
#include <SFML/Graphics.hpp>


int main() 
{ 

    constexpr int instructions_per_sec = 700;
    Clock clock(instructions_per_sec); 
    Memory mem; 
    Display display; 
    display.write_color(3, 31, Display::Color::WHITE);
    load_instructions("empty_program", mem);

    CPU cpu(mem, display);



    constexpr float cell_size = 10.0f; 

    sf::RenderWindow window(sf::VideoMode(320, 640), "Chip8");
    while (window.isOpen()) 
    {

        /* ---------- INSTRUCTION -------- */
        uint16_t instruction_bytes = cpu.fetch();
        Instruction instr = cpu.decode(instruction_bytes);
        cpu.execute(instr); 
        /* ------------------------------- */

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (size_t y = 0; y < display.vertical_pixels; y++)
        {
            for(size_t x = 0; x < display.horizontal_pixels; x++)
            {
                sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
                Display::Color color = display.read_color(y, x);
                if (color == Display::Color::BLACK)
                {
                    cell.setFillColor(sf::Color::Black);
                } 
                else if (color == Display::Color::WHITE)
                {
                    cell.setFillColor(sf::Color::White);
                }
                cell.setPosition(y * cell_size, x * cell_size);
                window.draw(cell);
            }
        }

        window.display(); 
        clock.wait_for_cycle(); 
    }
    return 0; 
}
