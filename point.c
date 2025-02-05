#include "point.h"


int valid_point(size_t w, size_t h, Point p) {
    return (p.x >= 0 && (size_t)p.x <= w) && 
           (p.y >= 0 && (size_t)p.y <= h);
}
