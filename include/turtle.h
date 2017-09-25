#ifndef _TURTLE_H
#define _TURTLE_H

#include <stdint.h>
#include "graphics.h"

struct turtle {
    float x, y, a;
    struct color c;
    struct image *img;
};

/* Move a turtle for a distance, optionally drawing a line. */
void move_turtle(struct turtle *t, float d, int pd);

/* Rotate a turtle. */
void turn_turtle(struct turtle *t, float r);

#endif
