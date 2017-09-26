// Initial test program

// Author: Matthew Knight
// File Name: main.cpp
// Date: 2017-09-25

#include "image.hpp"

int main(void)
{
    struct color black = {0, 0, 0};
    struct color white = {255, 255, 255};
    Image testImg(50, 50);
    
    testImg.fill(black);
    testImg.drawLine(0, 0, 49, 49, white);
    testImg.drawCircle(25, 25, 20, white);

    testImg.save("testImage.ppm");

    // test opening file
    struct image *img = open_bin_ppm("testImage.ppm");
    set_line(img, white, 50, 0, 0, 50);
    save_image(img, "textImage2.ppm");

    if (img)
	free_image(img);
}
