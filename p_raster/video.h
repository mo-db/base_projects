#ifndef VIDEO_H 
#define VIDEO_H

#include <stdint.h>
#include <stdio.h>

#define INIT_WIDTH 1280
#define INIT_HEIGHT 720
#define SCALING_FACTOR 4

struct Pixsurf {
    int w;
    int h;
    int n_pixels;
    uint32_t *pixels;
};

// set pixels to NULL if a new buffer should be allocated, free as whole
struct Pixsurf* create_new_pixsurf(int w, int h, uint32_t* pixels);
int draw_grid(struct Pixsurf* pixsurf);
int pixsurf_to_ppm(struct Pixsurf* pixsurf, FILE* fp);
struct Pixsurf* ppm_to_pixsurf(FILE* fp);

#endif
