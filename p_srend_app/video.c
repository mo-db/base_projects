#include "video.h"
#include "../base/include/libbase.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


// maybe instead of this allocate whole pb struct dyncamically 
// and also allocate the buf in the same malloc
struct scaled_surface *create_scaled_surface(Uint8 scaling_factor,
														SDL_Surface *surf)
{
	struct scaled_surface *s_surf = malloc(sizeof(struct scaled_surface));
	if (!s_surf) {
		BASE_PROCESS_ERROR("Could't malloc struct scaled_pixelbuf!");
		return NULL;
	}
	BASE_PROCESS_TRACE("malloc struct for scaled pixelbuf struct");

    s_surf->width = surf->w / scaling_factor;
    s_surf->height = surf->h / scaling_factor;
    s_surf->n_pixels = s_surf->width * s_surf->height;
	
	s_surf->pixels = malloc(s_surf->n_pixels * sizeof(Uint32));
    if (!s_surf->pixels) {
		BASE_PROCESS_ERROR("Could't create scaled_pixelbuf buf!");
        return NULL;
    }
	BASE_PROCESS_TRACE("malloc struct for scaled pixelbuf buffer");

	for (int i = 0; i < s_surf->n_pixels; i++) {
		s_surf->pixels[i] = 0xFFFFFFFF;
	}
    return s_surf;
}

int map_s_surf_to_surf(SDL_Surface *surf, struct scaled_surface *s_surf)
{
	// j = the scaled pixel width, l = how may small pixels in withd
	// k = how many small pixels in height
	int j = 0;
	// the parantheses with init_width are for testing
	for (int i = 0; i < s_surf->n_pixels; i++) {
		for (int k = 0; k < (SCALING_FACTOR * surf->w); k += surf->w) {
			for (int l = 0; l < SCALING_FACTOR; l++) {
				((uint32_t*)(surf->pixels))[j+l+k] = s_surf->pixels[i];
			}
		}
		if ((j + SCALING_FACTOR) % surf->w== 0) {
			// -1 to calculate for the row the program is on the end of
			j += (surf->w* (SCALING_FACTOR-1));
		}
		j += SCALING_FACTOR;
	}
	return 1;
}
