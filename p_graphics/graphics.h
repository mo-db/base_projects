#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../base/include/libbase.h"
#include "video.h"
#include "objects.h"
#include <stdint.h>

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









int map_s_surf_to_surf(SDL_Surface *surf, struct scaled_surface *s_surf);

//int destroy_struct_scaled_pixelbuf(struct scaled_pixelbuf *scaled_pb);
//int destroy_struct_pixelbuf(struct pixelbuf *);
//int destroy_struct_window_data(struct window_data *);
int draw_number(struct scaled_surface *s_surf, int number, uint32_t x_offset,
				uint32_t y_offset);
int draw_pixel_grid(struct scaled_surface *s_surf);
int draw_point(struct scaled_surface *s_surf, struct Point p);

int draw_rect(struct scaled_surface *s_surf, struct Rect *rect);
int new_draw_rect(struct scaled_surface *s_surf,
					 int x, int y, int w, int h, uint32_t color);

int draw_line_simple(struct scaled_surface *s_surf, struct Point p1,
					 struct Point p2);

#endif
