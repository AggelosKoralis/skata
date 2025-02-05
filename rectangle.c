
#include "point.h"



int draw_rectangle(uint32_t *pixels, size_t width, size_t height, Point coords, size_t rect_width, size_t rect_height, uint32_t color) {

    for (size_t _y = coords.y; _y < (coords.y + rect_height); _y++)
        if (coords.y + rect_height <= height)
            for (size_t _x = coords.x; _x < (coords.x + rect_width); _x++)
                if (coords.x + rect_width <= width) 
                    pixels[_y * width + _x] = color;

    return 0;
}



int draw_checker(uint32_t *pixels, size_t width, size_t height, size_t horizontal_num, size_t vertical_num, uint32_t color) {
    size_t recw = width / horizontal_num;
    size_t rech = height / vertical_num;

    int blank = 0;
    int loops = 0;

    for (size_t _y = 0; _y < height; _y += rech) {
        
        if (loops % 2 == 1)
            blank = 1;
        else 
            blank = 0;

        loops++;
        
        for (size_t _x = 0; _x < width; _x += recw) {
            if (blank) {blank = 0; continue;}
            
            blank = 1;
            Point rect_coords = {_x, _y};
            draw_rectangle(pixels, width, height, rect_coords, recw, rech, color);
        }
    }

    return 0;
}