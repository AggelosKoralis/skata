#ifndef RECT_H
#define RECT_H

#include <stdint.h>
#include <stdlib.h>

#include "point.h"

int draw_rectangle(
    uint32_t *pixels, 
    size_t width, 
    size_t height, 
    Point coords, 
    size_t rect_width, 
    size_t rect_height, 
    uint32_t color
);

int draw_checker(
    uint32_t *pixels, 
    size_t width, 
    size_t height, 
    size_t horizontal_num, 
    size_t vertical_num, 
    uint32_t color
);

#endif