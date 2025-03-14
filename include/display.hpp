

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
    Color read_color(unsigned int x_pixel, unsigned int y_pixel);
    void clear(); 
    constexpr static unsigned int vertical_pixels = 32; 
    constexpr static unsigned int horizontal_pixels = 64; 


  private:
    constexpr static unsigned int m_rows = vertical_pixels; 
    constexpr static unsigned int m_cols = horizontal_pixels; 
    std::array<Color, m_rows * m_cols> m_pixels;
};
