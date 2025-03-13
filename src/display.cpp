
#include "display.hpp"

Display::Display() { std::fill(m_pixels.begin(), m_pixels.end(), Display::BLACK); }

void Display::write_color(unsigned int x_pixel, unsigned int y_pixel, Display::Color color)
{
    m_pixels[x_pixel + m_cols * y_pixel] = color;
}


