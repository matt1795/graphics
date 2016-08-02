# graphics
Simple C graphics library for drawing images, turtle graphics and outputting video.

## Usage (still images and turtle graphics)
Example program to draw a tree using turtle graphics:
```c
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "turtle.h"

#define WIDTH 500
#define HEIGHT 350

/* Recursive function to draw branches of a tree. */
void draw_branch(
    int i,              /* how many more branches ahead */
    float a,            /* angle between branches */
    struct turtle *t
) {
    struct turtle t2;

    /* Stop if this is the last branch. */
    if (i == 0)
        return;

    /* Draw the branch. */
    move_turtle(t, 6 * i, 1);

    /* Duplicate this turtle to draw one of the child branches. */
    t2 = *t;

    /* Turn the two turtles in opposite directions. */
    turn_turtle(t, a);
    turn_turtle(&t2, -a);

    draw_branch(i - 1, a, t);
    draw_branch(i - 1, a, &t2);
}

int main(
    int arg,
    char *argv[]
) {
    struct image *img = new_image(WIDTH, HEIGHT);
    struct turtle t = {
        WIDTH / 2,
        HEIGHT - 1,
        0,
        (struct color){0, 0, 0},
        img
    };

    fill_image(img, (struct color){255, 255, 255});

    turn_turtle(&t, M_PI_2);

    draw_branch(10, M_PI / 6, &t);

    save_image(img, "hello.ppm");

    return 0;
}
```

To compile (assuming you've named the source code above turtle_test.c):

```
cc turtle_test.c graphics.c turtle.c -lm -o turtle_test
```

## Usage (video output)

Video output is 30 FPS.

In these examples, `stdout` is used as the file being written to. This can be any C `FILE` pointer.

Before drawing any frames, call `write_y4m_header`:

```
write_y4m_header(img, stdout);
```

When you're ready to output a frame:

```
write_y4m_frame(img, stdout);
```

If you've used `stdout` as your output file, you can pipe the program's output directly to a `.avi` file and play with any video player or into `avconv` to compress the video:

```
./my_graphics_program > hello.avi
mpv hello.avi
```
