#ifndef VIDEO_H
#define VIDEO_H

#include <SDL3/SDL.h>

struct window {
	Uint32 width;
	Uint32 height;
	SDL_Window *window;
	SDL_Surface *surface;
	Uint32 *buf;
    Uint32 n_pixels;
};

struct scaled_pixelbuf {
    Uint32 width;
    Uint32 height;
    Uint32 n_pixels;
    Uint8 scaling_factor;
    Uint32 *buf;
};

struct window *new_window_and_surface(Uint32 width, Uint32 height);
struct scaled_pixelbuf *new_scaled_pixelbuf_form_window(Uint8 scaling_factor,
														struct window *window);

int render(struct window *window_p, struct scaled_pixelbuf *sp_p);

int destroy_window_and_surface(struct window *window);
int destroy_scaled_pixelbuf(struct scaled_pixelbuf *scaled_pb);
#endif
