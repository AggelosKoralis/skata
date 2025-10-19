#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <stdlib.h>


typedef struct point {
    int x;
    int y;
} Point;


int valid_point(size_t width, size_t height, Point p);
int on_disk(Point center, size_t r, Point p);

#endif