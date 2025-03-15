
#include "hardware/keypad.hpp"

using namespace Hardware; 

Keypad::Keypad()
{
    std::fill(m_keys.begin(), m_keys.end(), 0); 
}

bool Keypad::is_pressed(size_t keynum)
{
    return m_keys[keynum];
}

void Keypad::set_pressed(size_t keynum, bool is_key_pressed)
{
    m_keys[keynum] = is_key_pressed; 
}
