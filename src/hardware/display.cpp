
#include "hardware/display.hpp"
#include <iostream> 

using namespace Hardware; 

Display::Display() { std::fill(m_pixels.begin(), m_pixels.end(), Display::Color::BLACK); }

void Display::write_color(size_t x_pixel, size_t y_pixel, Display::Color color)
{
    m_pixels.at(x_pixel + horizontal_pixels * y_pixel) = color;
}

Display::Color Display::read_color(size_t x_pixel, size_t y_pixel) const
{
    return m_pixels[x_pixel + horizontal_pixels * y_pixel];
}

void Display::clear()
{
    std::fill(m_pixels.begin(), m_pixels.end(), Display::Color::BLACK); 
}

bool Display::is_white(size_t x_pixel, size_t y_pixel) const
{
    return read_color(x_pixel, y_pixel) == Display::Color::WHITE; 
}

bool Display::is_black(size_t x_pixel, size_t y_pixel) const
{
    return read_color(x_pixel, y_pixel) == Display::Color::BLACK; 
}


