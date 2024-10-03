#include "debug.h"
#include "objects.h"
#include "video.h"
#include "graphics.h"
#include "state.h"
#include "logic.h"
#include <sdl3/sdl.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/* TESTING */
#ifdef TESTING
static const double TARGET_FPS = 1.0;
static const Uint64 TICK_DURATION_NS = (1000000000*((1.0/TARGET_FPS)/4.0));
#else
static const double TARGET_FPS = 120.0;
static const Uint64 TICK_DURATION_NS = (1000000000*((1.0/TARGET_FPS)/4.0));
#endif

// 320, 640, 960, 1280, 1600, 1920, 2240, 2560
#define INIT_WIDTH 1280
#define INIT_HEIGHT 720
#define SCALING_FACTOR 4

int main()
{
	if (!log_init(ERROR_LOGFILE, TRACE_LOGFILE)) {
		return 1;
	}
	LOG_TRACE("logging system and error handling initialized");

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
		PROCESS_ERROR("SDL initialization failure!");
		return 1;
	}
	LOG_TRACE("SDL initialized");

	//TODO: need something like other_init() or maybe state init? init for each import?
	// maybe have a struct with the state and give that struct to the update etc functions - so it's easier on the eyes and better maybe!
	pixel_counter = 1;

	struct window *main_window_p = new_window_and_surface(INIT_WIDTH, INIT_HEIGHT);
	if (!main_window_p) {
		return 1;
	}
	LOG_TRACE("main_window struct created");

	struct scaled_pixelbuf *main_sp_p = new_scaled_pixelbuf_form_window(SCALING_FACTOR, main_window_p);
	if (!main_sp_p) {
		return 1;
	}
	LOG_TRACE("Scaled pixel buffer created");

	// main loop
	SDL_Event event;
	Uint8 keep_going = 1;
	while (keep_going) {
		// poll for events 
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				keep_going = 0;
			}
			if (event.type == SDL_EVENT_KEY_DOWN) {
    			if (event.key.key == SDLK_A) {
				}
			}
		}
		/* SDL_DelayNS(1000); */
		//TODO: Refactor later
		SDL_Delay(10);
		if (pixel_counter == main_sp_p->height) {
			pixel_counter = 1;
		} else {
			pixel_counter++;
		}

		update(main_sp_p);
		if (!render(main_window_p, main_sp_p)) {
			return 1;
		}
	}
	//SDL_DestroyWindow(window.window);
	SDL_Quit();
	return 0;
}
