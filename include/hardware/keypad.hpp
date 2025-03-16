

#pragma once
#include <array> 
#include <cstdlib> 

namespace Hardware {

class Keypad
/*
    Stores 16 keys to be read from 
*/
{
public: 
    Keypad();
    bool is_pressed(size_t keynum);
    void set_pressed(size_t keynum, bool is_key_pressed);
    bool any_pressed();
    size_t get_key_pressed();
    
private: 
    static constexpr size_t m_num_keys = 16; 
    std::array<bool, m_num_keys> m_keys;
};

}