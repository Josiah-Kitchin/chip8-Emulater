

#pragma once
#include <array>

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
    void write_color(unsigned int x_pixel, unsigned int y_pixel, Color);
    Color read_color(unsigned int x_pixel, unsigned int y_pixel) const;
    void clear(); 
    constexpr static unsigned int vertical_pixels = 32; 
    constexpr static unsigned int horizontal_pixels = 64; 


  private:
    std::array<Color, vertical_pixels * horizontal_pixels> m_pixels;
};
