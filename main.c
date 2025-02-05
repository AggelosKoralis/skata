#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


#define WIDTH 400
#define HEIGHT 400

// canvas
uint32_t pixels[HEIGHT * WIDTH];


typedef struct point {
    int x;
    int y;
} Point;


typedef struct line {
    int a;
    int b;
} Line;


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
        uint8_t bytes[3] = { (pix[i] >> (8 * 0))& 0xFF, 
                             (pix[i] >> (8 * 1)) & 0xFF, 
                             (pix[i] >> (8 * 2)) & 0xFF };
       
        if (fwrite(bytes, sizeof(bytes), 1, f) != 1) return -1;
    }
    
    fclose(f);
    return 0;
}


int rectangle(uint32_t *pix, size_t w, size_t h, Point coords, size_t recw, size_t rech, uint32_t color) {

    for (size_t _y = coords.y; _y < (coords.y + rech); _y++)
        if (coords.y + rech <= h)
            for (size_t _x = coords.x; _x < (coords.x + recw); _x++)
                if (coords.x + recw <= w) 
                    pix[_y * w + _x] = color;

    return 0;
}


int checker(uint32_t *pix, size_t w, size_t h, size_t num_x, size_t num_y, uint32_t color) {
    size_t recw = w / num_x;
    size_t rech = h / num_y;

    int blank = 0;
    int loops = 0;

    for (size_t _y = 0; _y < h; _y += rech) {
        
        if (loops % 2 == 1)
            blank = 1;
        else 
            blank = 0;

        loops++;
        
        for (size_t _x = 0; _x < w; _x += recw) {
            if (blank) {blank = 0; continue;}
            
            blank = 1;
            Point rect_coords = {_x, _y};
            rectangle(pix, w, h, rect_coords, recw, rech, color);
        }
    }

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

int valid_point(uint32_t w, uint32_t h, Point p) {
    return (p.x >= 0 && (size_t)p.x <= w) && 
           (p.y >= 0 && (size_t)p.y <= h);
}


// PARALLEL TO THE X AXIS MAYBE I NEED TO SPECIFY THAT
// parallel side equation: y = a
// if there is a parallel side, return a
// else return -1
int parallel_side(Point p[3]) {
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


int triangle(uint32_t *pix, size_t w, size_t h, Point points[3], uint32_t color) {
    
    if (!(valid_point(w, h, points[0]) && 
          valid_point(w, h, points[1]) && 
          valid_point(w, h, points[2])))
        return -1;
   
    return 0;

}

int line(uint32_t *pix, size_t w, size_t h, Line line, uint32_t color) {

    for (size_t x = 0; x < w; x++) {
        size_t y = line.a * x + line.b;
        if (y <= h)
            pix[y * w + x] = color;
    }
    
    return 0;
}

int main() {
    
    // 0xaaBBGGRR
    fill(pixels, WIDTH, HEIGHT, 0xFFF06090);
   
    checker(pixels, WIDTH, HEIGHT, 10, 10, 0xFF000000);

    size_t recw = 260;
    size_t rech = 260;
    Point rectangle_coords = {WIDTH/2 - recw/2, HEIGHT/2 - rech/2};
    rectangle(pixels, WIDTH, HEIGHT, rectangle_coords, recw, rech, 0xFFF07415);
    
    
    //checker(pixels, WIDTH, HEIGHT, 10, 10, 0xFF000000);
    
    size_t radius = 120;
    Point center = {WIDTH/2, HEIGHT/2};
    circle(pixels, WIDTH, HEIGHT, center, radius, 0xFFFFFF00);

    //checker(pixels, WIDTH, HEIGHT, 10, 10, 0xFF000000);

    Line ln = {1, 0};
    uint32_t line_color = 0xFF0000FF;
    line(pixels, WIDTH, HEIGHT, ln, line_color);

    Line ln2 = {0, HEIGHT/2};
    line(pixels, WIDTH, HEIGHT, ln2, line_color);

    if (save_to_file(pixels, WIDTH, HEIGHT, "out.ppm") == -1) return -1;

    return 0;
}
