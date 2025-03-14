
#include <gtest/gtest.h>
#include "display.hpp"


TEST(display, write_color)
{
    Display display; 
    display.write_color(0, 0, Display::Color::WHITE);
    ASSERT_EQ(display.read_color(0, 0), Display::Color::WHITE);
    ASSERT_EQ(display.read_color(0, 1), Display::Color::BLACK);

    display.write_color(32, 12, Display::Color::WHITE);
    ASSERT_EQ(display.read_color(32, 12), Display::Color::WHITE);

    display.write_color(63, 31, Display::Color::WHITE);
    ASSERT_EQ(display.read_color(63, 31), Display::Color::WHITE);
}
