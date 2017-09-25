// C++ wrapper for color object in Preston Thompson's graphics library

// Author: Matthew Knight
// File Name: color.hpp
// Date: 2017-09-25

#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
#include <string>
#include "graphics.h"

class Color
{
    friend class Image;
    struct color c;

public:
    // default ctor
    Color();

    //ctor
    Color(uint8_t red, uint8_t green, uint8_t blue);
};

#endif
