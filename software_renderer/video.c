#include "video.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

struct window *new_window_and_surface(Uint32 width, Uint32 height)
{
	struct window *window_p = malloc(sizeof(struct window));
	PROCESS_ERROR("malloc struct winodow");
    window_p->width = width;
    window_p->height = height;
    window_p->n_pixels = width * height;

	window_p->window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									 width, height, SDL_WINDOW_METAL);
	if (!window_p->window) {
		PROCESS_ERROR("Could't create window!");
        return NULL;
	}
	PROCESS_ERROR("created SDL window");

	window_p->surface = SDL_GetWindowSurface(window_p->window);
	if (!window_p->surface) {
		PROCESS_ERROR("Could't create surface!");
        return NULL;
	}
	PROCESS_ERROR("created SDL surface");


	window_p->buf = (Uint32 *)window_p->surface->pixels;
	for (int i = 0; i < (window_p->n_pixels); i++) {
		window_p->buf[i] = 0xFFFFFFFF;
	}
	fprintf(stderr, "test\n");
    return window_p;
}

// maybe instead of this allocate whole pb struct dyncamically 
// and also allocate the buf in the same malloc
struct scaled_pixelbuf *new_scaled_pixelbuf_form_window(Uint8 scaling_factor,
														struct window *window_p)
{
	struct scaled_pixelbuf *scaled_pixelbuf_p = malloc(sizeof(struct scaled_pixelbuf));
	if (!scaled_pixelbuf_p) {
		PROCESS_ERROR("Could't create scaled_pixelbuf struct!");
		return NULL;
	}
	PROCESS_ERROR("malloc struct for scaled pixelbuf struct");

    scaled_pixelbuf_p->scaling_factor = scaling_factor;
    scaled_pixelbuf_p->width = window_p->width / scaling_factor;
    scaled_pixelbuf_p->height = window_p->height / scaling_factor;
    scaled_pixelbuf_p->n_pixels = scaled_pixelbuf_p->width * scaled_pixelbuf_p->height;
	
	scaled_pixelbuf_p->buf = malloc(scaled_pixelbuf_p->n_pixels * sizeof(Uint32));
    if (!scaled_pixelbuf_p->buf) {
		PROCESS_ERROR("Could't create scaled_pixelbuf buf!");
        return NULL;
    }
	PROCESS_ERROR("malloc struct for scaled pixelbuf buffer");

	for (int i = 0; i < scaled_pixelbuf_p->n_pixels; i++) {
		scaled_pixelbuf_p->buf[i] = 0xFFFFFFFF;
	}
    return scaled_pixelbuf_p;
}

int render(struct window *window_p, struct scaled_pixelbuf *sp_p)
{
	// j = the scaled pixel width, l = how may small pixels in withd
	// k = how many small pixels in height
	int j = 0;
	// the parantheses with init_width are for testing
	for (int i = 0; i < sp_p->n_pixels; i++) {
		for (int k = 0; k < (sp_p->scaling_factor * window_p->width); k += window_p->width) {
			for (int l = 0; l < sp_p->scaling_factor; l++) {
				window_p->buf[j+l+k] = sp_p->buf[i];
			}
		}
		if ((j + sp_p->scaling_factor) % window_p->width == 0) {
			// -1 to calculate for the row the program is on the end of
			j += (window_p->width * (sp_p->scaling_factor-1));
		}
		j += sp_p->scaling_factor;
	}
	SDL_UpdateWindowSurface(window_p->window);
	return 1;
}
