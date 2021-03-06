#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

// YCbCr conversion constants from RGB. You can find more information at 
// https://en.wikipedia.org/wiki/YCbCr.
static const float ycbcr[3][3] = {
    {0.257, 0.504, 0.098},
    {-0.148, -0.291, 0.439},
    {0.439, -0.368, -0.071}
};

// Creates a new image.
struct image *new_image(
    char type,				// Image type
    int w,				// width
    int h				// height
) {
    
    struct image* img = (struct image *)malloc(sizeof(struct image));
    
    // Make sure type is valid
    if (type == 'p')
	img->p = sizeof(struct color);
    else if (type == 'g')
	img->p = sizeof(uint8_t);
    else
	return NULL;
    

    img->w = w;
    img->h = h;
    img->b = malloc(w * h * img->p);

    return img;
}

// Open PPM or PGM file
struct image *open_file(const char* filename)
{
    FILE* input = fopen(filename, "r");

    if (!input)
	return NULL;

    char type_str[3], type;
    int max, h, w;
    
    fgets(type_str, 3, input);
    fscanf(input, "%d %d\n%d\n", &w, &h, &max);
    
    if (!strcmp(type_str, "P6"))
	type = 'p';
    else if (!strcmp(type_str, "P5"))
	type = 'g';
    else
	return NULL;

    struct image *img = new_image(type, w, h);
    fread(img->b, img->p, w*h, input);
    fclose(input);

    return img;
}

// Fill an image with a color.
void fill_image(
    struct image *img,
    void *c
) {
    int i;
    for (i = 0; i < img->w * img->h; i++)
	memcpy(img->b + i*img->p, c, img->p);
}

// Set a single pixel to a color.
void set_pixel(
    struct image *img,
    void *c,
    int x,
    int y
) {
    void *b = get_pixel(img, x, y);
    
    if (!b)
        return;
    
    memcpy(b, c, img->p);
}

// Get the color of a single pixel.
void *get_pixel(
    struct image *img,
    int x,
    int y
) {
    // Check if the pixel is in the image first.
    if (x >= img->w || x < 0)
        return NULL;
    if (y >= img->h || y < 0)
        return NULL;

    // Find the pixel in the image.
    void *b = img->b;
    b += img->p * img->w * y;
    b += img->p * x;

    return b;
}

// Draw a straight line between two points.
void set_line(
    struct image *img,
    void *c,
    int x0,
    int y0,
    int x1,
    int y1
) {
    // Bresenham's line algorithm
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        set_pixel(img, c, x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Draw a circle.
void set_circle(
    struct image *img,
    void *c,
    int x0,
    int y0,
    int r
) {
    // Midpoint circle algorithm
    int x = -r, y = 0, err = 2 - 2 * r;

    do {
        set_pixel(img, c, x0-x, y0+y);
        set_pixel(img, c, x0-y, y0-x);
        set_pixel(img, c, x0+x, y0-y);
        set_pixel(img, c, x0+y, y0+x);

        r = err;
        if (r <= y) err += ++y * 2 + 1;
        if (r > x || err > y) err += ++x * 2 + 1;

    } while (x < 0);
}

// convert between rgb and greyscale
int convert(struct image *img, char type)
{
    // process arguments
    char old_type;
    if (img->p == sizeof(struct color))
	old_type = 'p';
    else if (img->p == sizeof(uint8_t))
	old_type = 'g';
    else
	return -1;

    // No need to convert when...
    if (old_type == type)
	return 0;

    struct image *n_img = new_image(type, img->w, img->h);
    int i;

    if (type == 'g') {
	struct color *b = (struct color*)img->b;
	for (i = 0; i < img->w*img->h; i++) {
	    *(uint8_t*)(n_img->b + i) =	(b + i)->r*0.299 +
					(b + i)->g*0.587 +
					(b + i)->b*0.114;
	}
    }
    else if (type == 'p'){
	for (i = 0; i < img->w*img->h; i++)
	    memset(n_img + i*n_img->p, *(uint8_t*)(img->b + i), n_img->p);
    }
    else {
	return -1;
    }

    // transfer
    free(img->b);
    img->b = n_img->b;
    img->p = n_img->p;

    return 0;
}


// write image file to stream
int write_to_stream(struct image *img, FILE* stream)
{
    char type[3];

    if (img->p == sizeof(struct color))
	strncpy(type, "P6", sizeof(type));
    else if (img->p == sizeof(uint8_t))
	strncpy(type, "P5", sizeof(type));
    else
	return -1;
        
    fprintf(stream, "%s\n%d %d\n255\n", type, img->w, img->h);
    fwrite(img->b, img->p, img->w * img->h, stream);
    
    return 0;
}

// Save an image to a file in the Netpbm format.
int save_image(				// returns 0 on success, -1 on failure
    struct image *img,
    const char* filename
) {
    FILE* output = fopen(filename, "w");
    
    if (!output)
        return -1;

    write_to_stream(img, output);
    fclose(output);

    return 0;
}

// Write the YUV4MPEG2 header.
void write_y4m_header(
    struct image *img,
    FILE* output
) {
    fprintf(output, "YUV4MPEG2 ");
    fprintf(output, "W%d H%d ", img->w, img->h);
    fprintf(output, "F30:1 ");
    fprintf(output, "C444\n");
}

// Write a YUV4MPEG2 frame.
void write_y4m_frame(
    struct image* img,
    FILE* output
) {
    int i, y, cb, cr;
    float r, g, b;

    fprintf(output, "FRAME\n");
    struct color *buf = (struct color*)img->b;

    for (i = 0; i < img->w * img->h; i++) {
        r = buf[i].r;
        g = buf[i].g;
        b = buf[i].b;

        y = 16;
        y += (uint8_t)(ycbcr[0][0] * r + 0.5);
        y += (uint8_t)(ycbcr[0][1] * g + 0.5);
        y += (uint8_t)(ycbcr[0][2] * b + 0.5);

        fprintf(output, "%c", y);
    }

    for (i = 0; i < img->w * img->h; i++) {
        r = buf[i].r;
        g = buf[i].g;
        b = buf[i].b;

        cb = 128;
        cb += (uint8_t)(ycbcr[1][0] * r + 0.5);
        cb += (uint8_t)(ycbcr[1][1] * g + 0.5);
        cb += (uint8_t)(ycbcr[1][2] * b + 0.5);

        fprintf(output, "%c", cb);
    }

    for (i = 0; i < img->w * img->h; i++) {
        r = buf[i].r;
        g = buf[i].g;
        b = buf[i].b;

        cr = 128;
        cr += (uint8_t)(ycbcr[2][0] * r + 0.5);
        cr += (uint8_t)(ycbcr[2][1] * g + 0.5);
        cr += (uint8_t)(ycbcr[2][2] * b + 0.5);

        fprintf(output, "%c", cr);
    }
}

// Free an image.
void free_image(
    struct image *img
) {
    free(img->b);
    free(img);
}
