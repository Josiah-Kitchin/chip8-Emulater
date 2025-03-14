

#pragma once

#include "display.hpp"
#include "SFML/Graphics.hpp"

// Draws the pixels in the Display class to the sfml window 
void display_to_sfml_window(sf::RenderWindow& window, const Display& display, float cell_size); 