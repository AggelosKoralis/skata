#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "point.h"
// #include "line.h"
// #include "rectangle.h"
#include "canvas.h"

#define WIDTH 256 * 2
#define HEIGHT 256 * 2
// extern uint32_t pixels[HEIGHT * WIDTH];


void gradient(Canvas *canvas)
{
    size_t w = canvas->width, h = canvas->height;
    uint32_t *pix = canvas->pixels;

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {                            
            uint16_t left = y;
            uint16_t right = x;
            
           /* uint8_t bytes[3] = {
                                (left >> 4) & 0xFF,
                                (right >> 4) & 0xFF,
                                (right >> 4) & 0xFF
                               };
            
            */

            uint32_t color = (((left * 255) / h) << 16) | ((((left + right)) / (w + h)) << 8) | (((right * 255) / w) << 0);
            //uint32_t color = (bytes[0] << 8) | (bytes[1] << 0) | (bytes[2] << 0);
            pix[y * w + x] = color;
        }
    }
}


int valid_circle(Canvas *canvas, Point center, size_t r)
{
    size_t w = canvas->width, h = canvas->height;

    return 
    ((long)center.x - (long)r >= 0) &&
    ((long)center.y - (long)r >= 0) &&
    (center.x + r <= w) &&
    (center.y + r <= h);
}

int circle(Canvas *canvas, Point center, size_t r, uint32_t color)
{
    size_t w /* , h */;
    uint32_t *pix;
    Point p;
    
    if (!valid_circle(canvas, center, r)) return -1;
    
    w = canvas->width;
    // h = canvas->height;
    pix = canvas->pixels;

    for (size_t _y = (center.y - r); _y < (center.y + r); _y++) {
        for (size_t _x = (center.x - r); _x < (center.x + r); _x++){
            p.x = _x;
            p.y = _y;
            if (on_disk(center, r, p)) pix[_y * w + _x] = color;
        }
    }

    return 0;
}


// parallel side equation: y = a
// if there is a parallel side, return a
// else return -1
int parallel_side_to_xaxis(Point p[3])
{
    int ret = -1;
    
    if (p[0].y == p[1].y) ret = p[0].y;
    if (p[0].y == p[2].y) ret = p[0].y;
    if (p[1].y == p[2].y) ret = p[1].y;

    return ret;
}

Point miny(Point p[3])
{
    Point m_y = {p[0].x, p[0].y};
    
    if (m_y.y < p[1].y) {m_y.x = p[1].x; m_y.y = p[1].y;}
    if (m_y.y < p[2].y) {m_y.x = p[2].x; m_y.y = p[2].y;};

    return m_y;
}

Point maxy(Point p[3])
{
    Point m_y = {p[0].x, p[0].y};

    if (m_y.y > p[1].y) {m_y.x = p[1].x; m_y.y = p[1].y;};
    if (m_y.y > p[2].y) {m_y.x = p[2].x; m_y.y = p[2].y;};

    return m_y;
}

void swap_points(Point *p1, Point *p2)
{
    Point *temp = p1;
    p1 = p2;
    p2 = temp;
}

// ascending
void sort_points_by_y(Point p[3])
{
    for (int i = 0; i < 2; i++) {
        int min_idx = i;

        for (int j = i + 1; j < 3; j++)
            if (p[j].y < p[min_idx].y) min_idx = j;

        swap_points(&p[i], &p[min_idx]);
    }
}

/*
int triangle(uint32_t *pix, size_t w, size_t h, Point points[3], uint32_t color) {
    
    if (!(valid_point(w, h, points[0]) && 
          valid_point(w, h, points[1]) && 
          valid_point(w, h, points[2])))
        return -1;
   
    sort_points_by_y(points);

    Point miny, midy, maxy;


    int prl_side_height;
    if ((prl_side_height = parallel_side_to_xaxis(points)) != -1) {
        for (int _y = points[0].y; _y < points[2].y; _y++) {
            
        }

    }


    return 0;

}
*/

int main(int argc, char **argv)
{
    uint32_t color;
    Canvas *canvas = new_canvas(WIDTH, HEIGHT);
    if (!canvas) return 1;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // read falgs

            if (strlen(argv[i]) != 2) return 1;
            
            switch (argv[i][1]) {
            case 'g': // gradient
                
                gradient(canvas);
                break;
            case 'f': // fill
                color = (i + 1 < argc) ? atoi(argv[i + 1]) : 0;
                fill(canvas, color);
                break;
            case 'c': // circle
                break;
            case 'r': // rectangle
                break;
            case 't': // triangle
                break;
            case 'x': // checkerboard
                break;
            case 'i': // in file
                break;
            case 'o': // out file
                break;
            }
        
        }
    }

#if 0
    
    // 0xaaBBGGRR
    fill(pixels, WIDTH, HEIGHT, 0xFFF06090);
   
    draw_checker(pixels, WIDTH, HEIGHT, 10, 10, 0xFF000000);

    size_t recw = 260;
    size_t rech = 260;
    Point rectangle_coords = {WIDTH/2 - recw/2, HEIGHT/2 - rech/2};
    draw_rectangle(pixels, WIDTH, HEIGHT, rectangle_coords, recw, rech, 0xFFF07415);
    
    
    //draw_checker(pixels, WIDTH, HEIGHT, 10, 10, 0xFF000000);
    
    size_t radius = 120;
    Point center = {WIDTH/2, HEIGHT/2};
    circle(pixels, WIDTH, HEIGHT, center, radius, 0xFFFFbF00);

    //draw_checker(pixels, WIDTH, HEIGHT, 10, 10, 0xFF000000);

    Line ln = {1.0, 0.0};
    uint32_t line_color = 0xFF0000FF;
    draw_line(pixels, WIDTH, HEIGHT, ln, line_color);

    Line ln2 = {0.0, (float)HEIGHT/2};
    draw_line(pixels, WIDTH, HEIGHT, ln2, line_color);

    // triangle outline
    Point p1 = {100, 180};
    Point p2 = {230, 330};
    Point p3 = {150, 150};
    draw_line_section(pixels, WIDTH, HEIGHT, p1, p2, 0xFFFFFFFF);
    draw_line_section(pixels, WIDTH, HEIGHT, p1, p3, 0xFFFFFFFF);
    draw_line_section(pixels, WIDTH, HEIGHT, p2, p3, 0xFFFFFFFF);

#endif

    if (save_to_file(canvas, "out.ppm") == -1) return -1;

    return 0;
}
