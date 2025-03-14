
#include "display.hpp"
#include <iostream> 

Display::Display() { std::fill(m_pixels.begin(), m_pixels.end(), Display::Color::BLACK); }

void Display::write_color(unsigned int x_pixel, unsigned int y_pixel, Display::Color color)
{
    m_pixels[x_pixel + horizontal_pixels * y_pixel] = color;
}

Display::Color Display::read_color(unsigned int x_pixel, unsigned int y_pixel) const
{
    return m_pixels[x_pixel + horizontal_pixels * y_pixel];
}

void Display::clear()
{
    std::fill(m_pixels.begin(), m_pixels.end(), Display::Color::BLACK); 
}


