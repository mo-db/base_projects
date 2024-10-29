#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../base/include/libbase.h"
#include "objects.h"
#include "video.h"
#include <stdint.h>

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
