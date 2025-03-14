

#include "display_sfml.hpp"


void display_sfml(sf::RenderWindow& window, const Display& display, float cell_size)
/* 
    Draws the pixels in the Display class to the sfml window 
*/
{
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
}