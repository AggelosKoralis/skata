#include "canvas.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// canvas
uint32_t pixels[HEIGHT * WIDTH];

void fill(uint32_t *pix, size_t w, size_t h, uint32_t color) {
    for (size_t i = 0; i < h * w; i++)
        pix[i] = color;
}

int save_to_file(uint32_t *pix, size_t w, size_t h, char *fname) {
    
    FILE *f = fopen(fname, "wb");
    if (!f) return -1;

    fprintf(f, "P6\n%zu %zu\n255\n", w, h);

    for (size_t i = 0; i < w * h; i++) {
        // 0xBBGGRR
        uint8_t bytes[3] = { (pix[i] >> (8 * 0)) & 0xFF, 
                             (pix[i] >> (8 * 1)) & 0xFF, 
                             (pix[i] >> (8 * 2)) & 0xFF };
       
        if (fwrite(bytes, sizeof(bytes), 1, f) != 1) return -1;
    }
    
    fclose(f);
    return 0;
}