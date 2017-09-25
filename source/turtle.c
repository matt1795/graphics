#include <stdint.h>
#include <math.h>
#include "graphics.h"
#include "turtle.h"

/* Move a turtle for a distance, optionally drawing a line. */
void move_turtle(
    struct turtle *t,
    float d,            /* distance */
    int pd              /* 1 to draw a line, 0 to just move */
) {
    float x0 = t->x, y0 = t->y;

    t->x += d * cos(t->a);
    t->y += d * sin(t->a);

    if (pd)
        set_line(
            t->img,
            t->c,
            (int)(x0 + 0.5),
            (int)(y0 + 0.5),
            (int)(t->x + 0.5),
            (int)(t->y + 0.5)
        );
}

/* Rotate a turtle. */
void turn_turtle(
    struct turtle *t,
    float r             /* angle in radians */
) {
    t->a = fmod(t->a - r, 2 * M_PI);
}
