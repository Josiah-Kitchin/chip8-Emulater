

#include "display_sfml.hpp"


void display_to_sfml_window(sf::RenderWindow& window, const Display& display, float cell_size)
/* 
    Draws the pixels in the Display class to the sfml window 
*/
{
    sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
    for (size_t y = 0; y < display.vertical_pixels; y++)
    {
        for(size_t x = 0; x < display.horizontal_pixels; x++)
        {
            Display::Color color = display.read_color(x, y);
            if (color == Display::Color::BLACK)
            {
                cell.setFillColor(sf::Color::Black);
            } 
            else if (color == Display::Color::WHITE)
            {
                cell.setFillColor(sf::Color::White);
            }
            cell.setPosition(x * cell_size, y * cell_size);
            window.draw(cell);
        }
    }
}