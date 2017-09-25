// C++ wrapper for Preston Thompson's turtle object

// Author: Matthew Knight
// File Name: turtle.hpp
// Date: 2017-09-25

#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "turtle.h"
#include "image.hpp"

class Turtle
{
    struct turtle t;

public:
    //ctor
    Turtle(int x, int y, float a, Image& img, struct color c);

    // Move turtle, optionally drawing line
    void move(float d, int pd);

    // Rotate turtle
    void rotate(float r);
};

#endif
