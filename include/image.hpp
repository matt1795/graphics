// C++ wrapper for the image object in Preston's graphics library

// Author: Matthew Knight
// File Name: image.hpp
// Date: 2017-09-25

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <string>
#include "graphics.h"

class Image
{
    struct image *img;

public:
    // ctor
    Image(int w, int h);

    // fill image with color
    void fill(struct color c);

    // set color of pixel
    void set_pixel(int x, int y, struct color c);

    // get color of a pixel
    struct color *get_pixel(int x, int y);

    // draw line between points
    void draw_line(int x0, int y0, int x1, int y1, struct color c);

    // draw a circle
    void draw_circle(int x, int y, int r, struct color c);

    // save image to bitmap file
    int save(std::string filename);

    // Write YUV4MPEG2 header
    void write_y4m_header(FILE *output);
    
    // Write YUV4MPEG2 frame
    void write_y4m_frame(FILE *output);
    
    // dtor
    ~Image();

};

#endif
