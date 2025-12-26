#include "canvas.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// canvas
// uint32_t pixels[HEIGHT * WIDTH];


Canvas *new_canvas(size_t w, size_t h)
{
    Canvas *canvas;

    if (w == 0 || h == 0)
        return NULL;

    canvas = malloc(sizeof(Canvas));
    if (!canvas)
        return NULL;

    canvas->pixels = malloc(sizeof(uint32_t) * w * h);
    if (!canvas->pixels) {
        free(canvas);
        return NULL;
    }

    canvas->width = w;
    canvas->height = h;

    return canvas;
}

void fill(Canvas *canvas, uint32_t color)
{
    size_t w = canvas->width, h = canvas->height;
    for (size_t i = 0; i < h * w; i++)
        canvas->pixels[i] = color;
}

int save_to_file(Canvas *canvas, char *fname)
{
    FILE *outfile;
    size_t w, h;
    uint32_t *pix;

    outfile = fopen(fname, "wb");
    if (!outfile) return -1;

    w = canvas->width;
    h = canvas->height;
    pix = canvas->pixels;

    fprintf(outfile, "P6\n%zu %zu\n255\n", w, h);

    for (size_t i = 0; i < w * h; i++) {
        // 0xBBGGRR
        uint8_t bytes[3] = { (pix[i] >> (8 * 0)) & 0xFF, 
                             (pix[i] >> (8 * 1)) & 0xFF, 
                             (pix[i] >> (8 * 2)) & 0xFF };
       
        if (fwrite(bytes, sizeof(bytes), 1, outfile) != 1) return -1;
    }

    fclose(outfile);
    return 0;
}

void free_canvas(Canvas *canvas)
{
    if (!canvas)
        return;

    free(canvas->pixels);
    free(canvas);
}