

#pragma once
#include <array>

class Display
/* A black and white display, represented as a 64x32 matrix 
 * of BLACK or WHITE
 */
{
  public:
    enum Color
    {
        BLACK,
        WHITE
    };

    Display();
    void write_color(unsigned int x_pixel, unsigned int y_pixel, Color);

  private:
    constexpr static unsigned int m_rows = 64; 
    constexpr static unsigned int m_cols = 32; 
    std::array<Color, m_rows * m_cols> m_pixels;
};
