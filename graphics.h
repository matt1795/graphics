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
    int w;
    int h;
    struct color* b;
};

/* Creates a new image. */
struct image *new_image(int w, int h);

/* Fill an image with a color. */
void fill_image(struct image *img, struct color c);

/* Set a single pixel to a color. */
void set_pixel(struct image *img, struct color c, int x, int y);

/* Get the color of a single pixel. */
struct color *get_pixel(struct image *img, int x, int y);

/* Draw a straight line between two points. */
void set_line(struct image *img, struct color c, int x0, int y0, int x1, int y1);

/* Draw a circle. */
void set_circle(struct image *img, struct color c, int x0, int y0, int r);

/* Save an image to a file in the Netpbm format. */
int save_image(struct image *img, const char* filename);

/* Write the YUV4MPEG2 header. */
void write_y4m_header(struct image *img, FILE *output);

/* Write a YUV4MPEG2 frame. */
void write_y4m_frame(struct image *img, FILE *output);

/* Free an image. */
void free_image(struct image *img);

#endif
