#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdlib.h>


#define WIDTH 256 * 2
#define HEIGHT 256 * 2


void fill(uint32_t *pix, size_t w, size_t h, uint32_t color);
int save_to_file(uint32_t *pix, size_t w, size_t h, char *fname);


#endif