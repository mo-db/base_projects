#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../base/include/libbase.h"
#include "objects.h"
#include "video.h"
#include <stdint.h>

int draw_number(struct scaled_surface *sp_p, int number, uint32_t x_offset,
				uint32_t y_offset);
int draw_pixel_grid(struct scaled_surface *s_surf);
int draw_line_simple(struct scaled_surface *sp_p, struct Point p1, struct Point p2);

#endif
