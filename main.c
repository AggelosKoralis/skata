#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "point.h"
#include "line.h"
#include "rectangle.h"

#define WIDTH 400
#define HEIGHT 400

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


int valid_circle(size_t w, size_t h, Point center, size_t r) {
    return 
    ((long)center.x - (long)r >= 0) &&
    ((long)center.y - (long)r >= 0) &&
    (center.x + r <= w) &&
    (center.y + r <= h);
}

int on_disk(Point center, size_t r, size_t _x, size_t _y) {
    return 
    sqrt(
        pow((int)_x - (int)center.x, 2) + 
        pow((int)_y - (int)center.y, 2)
        ) <= r;
}

int circle(uint32_t *pix, size_t w, size_t h, Point center, size_t r, uint32_t color) {
    
    if (!valid_circle(w, h, center, r)) return -1;
    
    for (size_t _y = (center.y - r); _y < (center.y + r); _y++) 
        for (size_t _x = (center.x - r); _x < (center.x + r); _x++)
            if (on_disk(center, r, _x, _y)) 
                pix[_y * w + _x] = color;

    return 0;
}


// parallel side equation: y = a
// if there is a parallel side, return a
// else return -1
int parallel_side_to_xaxis(Point p[3]) {
    int ret = -1;
    
    if (p[0].y == p[1].y) ret = p[0].y;
    if (p[0].y == p[2].y) ret = p[0].y;
    if (p[1].y == p[2].y) ret = p[1].y;

    return ret;
}

Point miny(Point p[3]) {
    Point m_y = {p[0].x, p[0].y};
    
    if (m_y.y < p[1].y) {m_y.x = p[1].x; m_y.y = p[1].y;}
    if (m_y.y < p[2].y) {m_y.x = p[2].x; m_y.y = p[2].y;};

    return m_y;
}

Point maxy(Point p[3]) {
    Point m_y = {p[0].x, p[0].y};

    if (m_y.y > p[1].y) {m_y.x = p[1].x; m_y.y = p[1].y;};
    if (m_y.y > p[2].y) {m_y.x = p[2].x; m_y.y = p[2].y;};

    return m_y;
}

void swap_points(Point *p1, Point *p2) {
    Point *temp = p1;
    p1 = p2;
    p2 = temp;
}

// ascending
void sort_points_by_y(Point p[3]) {
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

int main() {
    
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


    if (save_to_file(pixels, WIDTH, HEIGHT, "out.ppm") == -1) return -1;

    return 0;
}
