

#pragma once
#include <array>
#include <cstdlib> 
#include "memory.hpp"

class Display
/* A black and white display, represented as a 64x32 matrix 
 * of BLACK or WHITE
 */
{
  public:
    enum class Color
    {
        BLACK,
        WHITE
    };

    Display();
    void write_color(size_t x_pixel, size_t y_pixel, Color);
    Color read_color(size_t x_pixel, size_t y_pixel) const;

    bool is_white(size_t x_pixel, size_t y_pixel) const;
    bool is_black(size_t x_pixel, size_t y_pixel) const;

    void clear(); 
    constexpr static unsigned int vertical_pixels = 32; 
    constexpr static unsigned int horizontal_pixels = 64; 

  private:
    std::array<Color, vertical_pixels * horizontal_pixels> m_pixels;

};



