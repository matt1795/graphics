// Test program for c portion of the graphics library

// Author: Matthew Knight
// File Name; cTest.c
// Date: 2017-09-25

// This program uses simple assert macros to verify the proper operation of the
// C functions

#include <stdio.h>
#include <assert.h>
#include "graphics.h"

int main(void)
{
    struct color red = {255, 0, 0};
    struct color green = {0, 255, 0};
    struct color blue = {0, 0, 255};
    uint8_t white = 255;
    uint8_t grey = 127;
    uint8_t black = 0;

    // make a color image
    struct image *color_image = new_image('p', 50, 50);
    assert(color_image != NULL);
    assert(color_image->b != NULL);

    fill_image(color_image, &green);
    set_line(color_image, &red, 0, 0, 49, 49);
    set_circle(color_image, &blue, 25, 25, 20);

    assert(save_image(color_image, "color_image.ppm") == 0);

    // make a greyscale image
    struct image *grey_image = new_image('g', 50, 50);
    assert(grey_image != NULL);
    assert(grey_image->b != NULL);
    
    fill_image(grey_image, &grey);
    set_line(grey_image, &black, 0, 0, 49, 49);
    set_circle(grey_image, &white, 25, 25, 20);
    
    assert(save_image(grey_image, "grey_image.ppm") == 0);

    // open a test file
    struct image *lena = open_file("lena.ppm");
    assert(lena != NULL);
    assert(lena->b != NULL);
    
    assert(convert(lena, 'd') != 0);
    assert(convert(lena, 'p') == 0);
    assert(convert(lena, 'g') == 0);
    assert(save_image(lena, "lena_grey.pgm") == 0);

    free_image(color_image);
    free_image(grey_image);
    free_image(lena);

    printf("Testing successful!\n");
}
