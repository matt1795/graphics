#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdio.h>
#include <stdint.h>

struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct image {
    int w;				// image width
    int h;				// image height
    size_t p;				// size of pixel
    void *b;				// image buffer
};

// Creates a new image.
struct image *new_image(char type, int w, int h);

// Open PPM or PGM from file
struct image *open_file(const char* filename);

// Fill an image with a color.
void fill_image(struct image *img, void *c);

// Set a single pixel to a color.
void set_pixel(struct image *img, void *c, int x, int y);

// Get the color of a single pixel.
void *get_pixel(struct image *img, int x, int y);

// Draw a straight line between two points.
void set_line(struct image *img, void *c, int x0, int y0, int x1, int y1);

// Draw a circle.
void set_circle(struct image *img, void *c, int x0, int y0, int r);

// convert between rgb and greyscale
int convert(struct image *img, char type);

// Write PPM/PGM file to a stream
int write_to_stream(struct image *img, FILE* stream);

// Save an image to a file in the Netpbm format.
int save_image(struct image *img, const char* filename);

// Write the YUV4MPEG2 header.
void write_y4m_header(struct image *img, FILE *output);

// Write a YUV4MPEG2 frame.
void write_y4m_frame(struct image *img, FILE *output);

// Free an image.
void free_image(struct image *img);

#endif
