#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdlib.h>


// #define WIDTH 256 * 2
// #define HEIGHT 256 * 2

typedef struct {
    uint32_t *pixels;
    size_t width;
    size_t height;
} Canvas;

Canvas *new_canvas(size_t w, size_t h);
void fill(Canvas *canvas, uint32_t color);
int save_to_file(Canvas *canvas, char *fname);
void free_canvas(Canvas *canvas);

#endif