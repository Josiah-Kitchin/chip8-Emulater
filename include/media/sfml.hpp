

#pragma once

#include "hardware/display.hpp"
#include "hardware/keypad.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace Media {

// Draws the pixels in the Display class to the sfml window 
void display_to_sfml_window(sf::RenderWindow& window, const Hardware::Display& display, float cell_size); 
void handle_sfml_keypad(const sf::Event& event, Hardware::Keypad& keypad);
sf::Sound get_sound_from_file(const std::string& file_name);

}