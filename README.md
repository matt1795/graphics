# "supercharged" graphics library

Simple C graphics library with C++ wrapper for drawing images, turtle graphics
and outputting video.

I have yet to get into documentation yet, here are my additions to the old
library so far (C):

- Opening of files
- Representation of color or greyscal images
- Converting data between color/greyscale
- Writing to streams

For efficiency's sake I use void pointers to deal with the difference in
color/greyscale data structures. It is expected that the programmer understands
which datatype the image is and makes acts accordingly. If a color pixel is
written to a greyscale image it will in fact write 3 greyscale images.

Moving forward, I want to change the color representation of the image from RGB
to YCbCr. This would not change the image buffer sizing, but it makes consecutive 
image processing operations far more efficient.

The C++ wrapper only works for the original library. Once I get YCbCr goinging,
I can flesh out an image processing library using classes. 

Image processing features to add:

- Manipulation
    - translation
    - rotation
    - scaling
- Point Processing
    - linear
    - gamma
    - logarithmic
    - auto-contrast adjustment
- Histogram Processing
    - equalization
    - matching
    - local
- Spacial Filtering
    - high pass
    - low pass
    - custom

More will be added to the list as I go through my image processing course.
