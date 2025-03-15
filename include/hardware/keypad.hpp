

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
    
private: 
    std::array<bool, 16> m_keys;
};

}