#include "point.h"
#include <math.h>

int valid_point(size_t w, size_t h, Point p) {
    return (p.x >= 0 && (size_t)p.x <= w) && 
           (p.y >= 0 && (size_t)p.y <= h);
}

// is p on the disk (center, r)?
int on_disk(Point center, size_t r, Point p) {
    return 
    sqrt(
        pow((int)p.x - (int)center.x, 2) + 
        pow((int)p.y - (int)center.y, 2)
        ) <= r;
}
