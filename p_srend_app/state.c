#include <SDL2/SDL.h>
#include "state.h"
#include "video.h"
#include "graphics.h"
#include "objects.h"
#include <stdlib.h>

/* int update_graphics(struct scaled_surface *s_surf, struct State *state) */
int update_graphics(struct scaled_surface *s_surf)
{
	if (!draw_pixel_grid(s_surf)) {
		return 0;
	}

	// draw white again
	for (int i = 0; i < s_surf->n_pixels; i++) {
		s_surf->pixels[i] = 0xFFFFFFFF;
	}
	
	struct Point p1;
	p1.x = 1;
	p1.y = 1;
	struct Point p2;
	p2.x = s_surf->width;
	/* p2.y = pixel_counter; */
	p2.y = 30;

	if (!draw_line_simple(s_surf, p1, p2)) {
		return 0;
	}

	return 1;
}
