// C++ wrapper for the image object in Preston's graphics library

// Author: Matthew Knight
// File Name: image.hpp
// Date: 2017-09-25

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <string>
#include "graphics.h"
#include "color.hpp"

class Image
{
    struct image;

public:
    // ctor
    Image(int w, int h);

    // fill image with color
    void fill(Color& c);

    // set color of pixel
    void set_pixel(int x, int y, Color& c);

    // get color of a pixel
    Color& get_pixel(int x, int y);

    // draw line between points
    void draw_line(int x0, int y0, int x1, int y1, Color& c);

    // draw a circle
    void draw_circle(int x, int y, int r, Color& c);

    // save image to bitmap file
    void save(std::string filename);

    // Write YUV4MPEG2 header
    void write_y4m_header(FILE *output);
    
    // Write YUV4MPEG2 frame
    void write_y4m_frame(FILE *output);
    
    // dtor
    ~Image();

};

#endif
