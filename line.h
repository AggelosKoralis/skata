#ifndef LINE_H
#define LINE_H

#include <stdint.h>
#include <stdlib.h>

#include "point.h"

typedef struct line {
    float a;
    float b;
} Line;


int draw_line(
    uint32_t *pixels, 
    size_t width, 
    size_t height, 
    Line line, 
    uint32_t color
);

int draw_line_section(
    uint32_t *pixels, 
    size_t width, 
    size_t height, 
    Point p1, 
    Point p2, 
    uint32_t color
);

#endif