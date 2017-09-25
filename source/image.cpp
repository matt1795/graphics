// C++ wrapper for the image object in Preston's graphics library

// Author: Matthew Knight
// File Name: image.cpp
// Date: 2017-09-25

#include "image.hpp"

// ctor
Image::Image(int w, int h)
    : img(new_image(w, h))
{}

// fill image with color
void Image::fill(struct color c)
{
    fill_image(img, c);
}

// set color of pixel
void Image::set_pixel(int x, int y, struct color c)
{
    set_pixel(img, c, x, y);
}

// get color of a pixel
struct color *Image::get_pixel(int x, int y)
{
    return get_pixel(img, x, y);
}

// draw line between points
void Image::draw_line(int x0, int y0, int x1, int y1, struct color c)
{
    set_line(img, c, x0, y0, x1, y1);
}

// draw a circle
void Image::draw_circle(int x, int y, int r, struct color c)
{
    set_circle(img, c, x, y, r);
}

// save image to bitmap file
int Image::save(std::string filename)
{
    return save_image(img, filename.c_str());
}

// Write YUV4MPEG2 header
void Image::write_y4m_header(FILE *output)
{
    write_y4m_header(img, output);
}

// Write YUV4MPEG2 frame
void Image::write_y4m_frame(FILE *output)
{
    write_y4m_frame(img, output);
}

// dtor
~Image::Image()
{
    free_image(img);
}
