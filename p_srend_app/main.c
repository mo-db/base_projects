#include <SDL2/SDL.h>
#include "../base/include/libbase.h"
#include "video.h"
#include "state.h"
#include "stdio.h"
#include "stdint.h"

static SDL_Window *window;
static SDL_Surface *surface;
static struct scaled_surface *s_surf;
static SDL_Event event;

static int mouse_x;
static int mouse_y;
static int mouse_down;

static int imgui_active;
static int imgui_highlight;
static int imgui_id;

/* static struct State *state; */

int main(int argc, char** argv)
{
	if (!base_log_init()) {
		fprintf(stderr, "Failed to init log and error system");
		return 1;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO
			  | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
		// hum_error HUM_ERROR
		// hum_trace HUM_TRACE
		BASE_PROCESS_ERROR("Error SDL init");
		return 0;
	}

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, INIT_WIDTH,
								INIT_HEIGHT, SDL_WINDOW_METAL);
	if (!window) {
		BASE_PROCESS_ERROR("SDL_CreateWindow() null return!");
        return 1;
	}

	surface = SDL_GetWindowSurface(window);
	if (!surface) {
		BASE_PROCESS_ERROR("SDL_GetWindowSurface() null return!");
        return 1;
	}

	s_surf = create_scaled_surface(SCALING_FACTOR, surface);
	if (!s_surf) {
		BASE_PROCESS_ERROR("create_scaled_pixelbuf() null return!");
		return 1;
	}

	uint8_t keep_going = 1;
	while (keep_going) {
		// poll for events 
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					keep_going = 0;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_b) {
						keep_going = 0;
					}
				case SDL_MOUSEMOTION:
					mouse_x = event.motion.x;
					mouse_x = event.motion.x;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouse_down = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					mouse_down = 0;
					break;
			}
		}

		/* if (!update_graphics(s_surf, state)) */
		if (!update_graphics(s_surf))
			return 1;
		/* if (!update_audio(NULL)) */
			/* return 1; */
		if (!map_s_surf_to_surf(surface, s_surf))
			return 1;
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 42;
}
