#ifndef LINE_H
#define LINE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct line {
    int a;
    int b;
} Line;


int draw_line(
    uint32_t *pixels, 
    size_t width, 
    size_t height, 
    Line line, 
    uint32_t color
);


#endif