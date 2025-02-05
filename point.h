#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <stdlib.h>


typedef struct point {
    int x;
    int y;
} Point;


int valid_point(size_t width, size_t height, Point p);


#endif