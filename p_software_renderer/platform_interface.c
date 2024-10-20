#include <SDL2/SDL.h>
#include "platform_interface.h"
#include "../base/include/libbase.h"
#include "video.h"

int platif_init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
		return 0;
	}
	return 1;
}

/*********
 * VIDEO *
 *********/
void *platif_create_window(int width, int height)
{
	SDL_Window *window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									 	width, height, SDL_WINDOW_METAL);
	if (!window) {
        return NULL;
	}
	return (void*)window;
}

void *platif_get_window_surface(void *window_handle)
{
	SDL_Surface *surface = SDL_GetWindowSurface(window_handle);
	if (!surface) {
        return NULL;
	}
	return (void*)surface;
}

struct window_data *platif_get_window_data(void *window_handle)
{
	SDL_Window *window = (SDL_Window*)window_handle;
	struct window_data *wd = malloc(sizeof(struct window_data));
	BASE_PROCESS_TRACE("malloc struct window_data");
	
	SDL_GetWindowSize(window, &(wd->width), &(wd->height));

	return wd;
}

struct pixelbuf *platif_get_surface_pixelbuf(void *surface_handle)
{
	SDL_Surface *surface = (SDL_Surface*)surface_handle;
	struct pixelbuf *pb = malloc(sizeof(struct pixelbuf));
	BASE_PROCESS_TRACE("malloc struct pixelbuf");

	pb->width = surface->w; pb->height = surface->h;
	pb->n_pixels = pb->width * pb->height;
	pb->buf = (uint32_t*)surface->pixels;

	for (int i = 0; i < (pb->n_pixels); i++) {
		pb->buf[i] = 0xFFFFFFFF;
	}
	return pb;
}

int platif_render_surface(void *window_handle)
{
	SDL_Window *window = (SDL_Window*)window_handle;
	SDL_UpdateWindowSurface(window);
	return 0;
}

void platif_quit()
{
	SDL_Quit();
}

//int update_window_data(void *window_handle, struct window_data *data);
//int update_pixelbuf(void *surface_handle, struct pixelbuf *pb);

//int platif_destroy_surface(void *window_handle);
//int platif_destroy_window(void *window_handle);

