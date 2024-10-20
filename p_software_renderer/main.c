#include "../base/include/libbase.h"
#include "video.h"
#include "state.h"
#include "logic.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>

// TODO: define two preprocessor states, one for a loop and one for static execution
// like with the turtle program - use?
// so would be per hand execution - wouldnt it be better to have cli input with loop?
//
// INFO: -> static input to begin with - should be better for turtle program


// #INFO: I should seperate the code that is library dependant from the
// the code that doesn't need a library to compile. Thats one of the big
// points of this idea right? to do all rendering and calculations internally
// and then just hand a (surface) array over to an interface that gets the
// pixels to the screen. Same for audio, but for audio i at least can just
// use miniaudio which is only header based.

// #INFO: so what things are os dependent?:
// - output of pixel array to screen
// - timer
// - user events

// WARN: Seperating the code that needs to interface with the system and 
// the code that only depends on C, Standard Library, and my own logic 
// and functions enables me to even port the code to webassembly if i can
// just swich out the interface functions..

/* TESTING */
/* #ifdef TESTING */
/* static const double TARGET_FPS = 1.0; */
/* static const Uint64 TICK_DURATION_NS = (1000000000*((1.0/TARGET_FPS)/4.0)); */
/* #else */
/* static const double TARGET_FPS = 120.0; */
/* static const Uint64 TICK_DURATION_NS = (1000000000*((1.0/TARGET_FPS)/4.0)); */
/* #endif */

// 320, 640, 960, 1280, 1600, 1920, 2240, 2560
#define INIT_WIDTH 1280
#define INIT_HEIGHT 720
#define SCALING_FACTOR 4

int main()
{
	if (!b_log_init()) { return 1; }
	BASE_PROCESS_TRACE("logging system and error handling initialized");


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
		BASE_PROCESS_ERROR("SDL initialization failure!");
		fprintf(stderr, "bla");
		return 1;
	}
	BASE_PROCESS_TRACE("SDL initialized");

	struct window *main_window_p = new_window_and_surface(INIT_WIDTH, INIT_HEIGHT);
	if (!main_window_p) {
		BASE_PROCESS_ERROR("Window/Surface couldn't be created!");
		return 1;
	}
	BASE_PROCESS_TRACE("main_window struct created");

	struct scaled_pixelbuf *main_sp_p = new_scaled_pixelbuf_form_window(SCALING_FACTOR, main_window_p);
	if (!main_sp_p) {
		BASE_PROCESS_ERROR("Scaled Pixelbuf couldn't be created!");
		return 1;
	}
	BASE_PROCESS_TRACE("Scaled pixel buffer created");

	// main loop
	SDL_Event event;
	Uint8 keep_going = 1;
	while (keep_going) {
		// poll for events 
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				keep_going = 0;
			}
			if (event.type == SDL_KEYDOWN) {
    			if (event.key.keysym.sym == SDLK_b) {
					keep_going = 0;
				}
			}
		}
		//TODO: Refactor later
		if (pixel_counter == main_sp_p->height) {
			pixel_counter = 1;
		} else {
			pixel_counter++;
		}

		if (!update(main_sp_p)) {
			return 1;
		}
		if (!render(main_window_p, main_sp_p)) {
			return 1;
		}

	}
	SDL_DestroyWindow(main_window_p->window);
	SDL_Quit();

	return 0;
}
