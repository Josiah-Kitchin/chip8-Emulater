
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

bool Keypad::any_pressed()
{
    for (bool key : m_keys)
        if (key) return key; 
    return false; 
}

size_t Keypad::get_key_pressed()
// Should only be called if there is a key pressed
{
    for (size_t i = 0; i < m_num_keys; i++)
    {
        if (m_keys[i]) return i;
    }
    return 0; 
}


void Keypad::set_pressed(size_t keynum, bool is_key_pressed)
{
    m_keys[keynum] = is_key_pressed; 
}
