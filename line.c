#include "line.h"
#include <stdio.h>
int draw_line(uint32_t *pix, size_t w, size_t h, Line line, uint32_t color) {

    for (size_t x = 0; x < w; x++) {
        size_t y = line.a * x + line.b;
        if (y <= h)
            pix[y * w + x] = color;
    }
    
    return 0;
}

int draw_line_section(uint32_t *pixels, size_t width, size_t height, Point p1, Point p2, uint32_t color) {

    if (!valid_point(width, height, p1) && !valid_point(width, height, p2))
        return -1;

    int a, b;
    
    if (p1.x == p2.x) {a = 0;}
    else a = (p2.y - p1.y) / (p2.x - p1.x);

    b = p1.y - a * p1.x;

    int startx = p2.x,  endx = p1.x;
    if (p1.x < p2.x) {startx = p1.x; endx = p2.x;}

    for (int _x = startx; _x < endx; _x++) {
        int y0 = a * _x + b;
        pixels[y0 * width + _x] = color;
    }

    return 0;
}
