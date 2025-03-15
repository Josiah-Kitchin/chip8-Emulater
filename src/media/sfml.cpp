

#include "media/sfml.hpp"


void Media::display_to_sfml_window(sf::RenderWindow& window, const Hardware::Display& display, float cell_size)
/* 
    Draws the pixels in the Display class to the sfml window 
*/
{
    sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
    for (size_t y = 0; y < display.vertical_pixels; y++)
    {
        for(size_t x = 0; x < display.horizontal_pixels; x++)
        {
            Hardware::Display::Color color = display.read_color(x, y);
            if (color == Hardware::Display::Color::BLACK)
            {
                cell.setFillColor(sf::Color::Black);
            } 
            else if (color == Hardware::Display::Color::WHITE)
            {
                cell.setFillColor(sf::Color::White);
            }
            cell.setPosition(x * cell_size, y * cell_size);
            window.draw(cell);
        }
    }
}

void Media::handle_sfml_keypad(const sf::Event& event, Hardware::Keypad& keypad)
/*
    Set corresponding key in the keypad to pressed or unpressed on key event
*/
{
    bool is_key_pressed = event.type == sf::Event::KeyPressed; 
    switch (event.key.code)
    {
        case sf::Keyboard::Num1:
            keypad.set_pressed(0, is_key_pressed); 
            break; 
        case sf::Keyboard::Num2:
            keypad.set_pressed(1, is_key_pressed); 
            break; 
        case sf::Keyboard::Num3:
            keypad.set_pressed(2, is_key_pressed); 
            break; 
        case sf::Keyboard::Num4:
            keypad.set_pressed(3, is_key_pressed); 
            break; 
        case sf::Keyboard::Q:
            keypad.set_pressed(4, is_key_pressed); 
            break; 
        case sf::Keyboard::W:
            keypad.set_pressed(5, is_key_pressed); 
            break; 
        case sf::Keyboard::E:
            keypad.set_pressed(6, is_key_pressed); 
            break; 
        case sf::Keyboard::R:
            keypad.set_pressed(7, is_key_pressed); 
            break; 
        case sf::Keyboard::A:
            keypad.set_pressed(8, is_key_pressed); 
            break; 
        case sf::Keyboard::S:
            keypad.set_pressed(9, is_key_pressed); 
            break; 
        case sf::Keyboard::D:
            keypad.set_pressed(10, is_key_pressed); 
            break; 
        case sf::Keyboard::F:
            keypad.set_pressed(11, is_key_pressed); 
            break; 
        case sf::Keyboard::Z:
            keypad.set_pressed(12, is_key_pressed); 
            break; 
        case sf::Keyboard::X:
            keypad.set_pressed(13, is_key_pressed); 
            break; 
        case sf::Keyboard::C:
            keypad.set_pressed(14, is_key_pressed); 
            break; 
        case sf::Keyboard::V:
            keypad.set_pressed(15, is_key_pressed); 
            break; 
    }
}