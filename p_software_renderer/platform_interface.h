#ifndef PLATFORM_INTERFACE_H
#define PLATFORM_INTERFACE_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include "../base/include/libbase.h"
#include "video.h"

int platif_init();
// returns opague handle for window
void *platif_create_window(int widht, int height);
// returns opague handle for surface
void *platif_get_window_surface(void *window_handle);

struct window_data *platif_get_window_data(void *window_handle);
struct pixelbuf *platif_get_surface_pixelbuf(void *surface_handle);

int platif_render_surface(void *window_handle);

int update_window_data(void *window_handle, struct window_data *data);
int update_pixelbuf(void *surface_handle, struct pixelbuf *pb);

int platif_destroy_surface(void *window_handle);
int platif_destroy_window(void *window_handle);

void platif_quit();

#endif

