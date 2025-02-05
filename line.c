#include "line.h"

int draw_line(uint32_t *pix, size_t w, size_t h, Line line, uint32_t color) {

    for (size_t x = 0; x < w; x++) {
        size_t y = line.a * x + line.b;
        if (y <= h)
            pix[y * w + x] = color;
    }
    
    return 0;
}