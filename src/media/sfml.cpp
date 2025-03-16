

#include "media/sfml.hpp"
#include <iostream> 


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

sf::Sound Media::get_sound_from_file(const std::string& file_name)
{
    sf::SoundBuffer buffer; 
    if (!buffer.loadFromFile(file_name));
    {
        std::cout << "Failed to load sound file: " << file_name << std::endl; 
        std::exit(EXIT_FAILURE);
    }

    sf::Sound sound; 
    sound.setBuffer(buffer);
    return sound; 
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
            keypad.set_pressed(0x01, is_key_pressed); 
            break; 
        case sf::Keyboard::Num2:
            keypad.set_pressed(0x02, is_key_pressed); 
            break; 
        case sf::Keyboard::Num3:
            keypad.set_pressed(0x03, is_key_pressed); 
            break; 
        case sf::Keyboard::Num4:
            keypad.set_pressed(0x0C, is_key_pressed); 
            break; 
        case sf::Keyboard::Q:
            keypad.set_pressed(0x04, is_key_pressed); 
            break; 
        case sf::Keyboard::W:
            keypad.set_pressed(0x05, is_key_pressed); 
            break; 
        case sf::Keyboard::E:
            keypad.set_pressed(0x06, is_key_pressed); 
            break; 
        case sf::Keyboard::R:
            keypad.set_pressed(0x0D, is_key_pressed); 
            break; 
        case sf::Keyboard::A:
            keypad.set_pressed(0x07, is_key_pressed); 
            break; 
        case sf::Keyboard::S:
            keypad.set_pressed(0x08, is_key_pressed); 
            break; 
        case sf::Keyboard::D:
            keypad.set_pressed(0x09, is_key_pressed); 
            break; 
        case sf::Keyboard::F:
            keypad.set_pressed(0x0E, is_key_pressed); 
            break; 
        case sf::Keyboard::Z:
            keypad.set_pressed(0x0A, is_key_pressed); 
            break; 
        case sf::Keyboard::X:
            keypad.set_pressed(0x00, is_key_pressed); 
            break; 
        case sf::Keyboard::C:
            keypad.set_pressed(0x0B, is_key_pressed); 
            break; 
        case sf::Keyboard::V:
            keypad.set_pressed(0x0F, is_key_pressed); 
            break; 
    }
}
