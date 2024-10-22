#include "../base/include/libbase.h"
#include "platform_interface.h"
#include <stdint.h>
#include "video.h"
#include "state.h"
#include "logic.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

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
	if (!base_log_init()) {
		BASE_PROCESS_ERROR("Couldn't initialise logging and error system");
		return 1;
	}
	BASE_PROCESS_TRACE("Logging and error system initialized");

	if (!platif_init()) {
		BASE_PROCESS_ERROR("Couldn't initialise platfrom interface");
		return 1;
	}
	BASE_PROCESS_TRACE("Platform interface initialised");

	void *main_window_handle = platif_create_window(INIT_WIDTH, INIT_HEIGHT);
	if (!main_window_handle) {
		BASE_PROCESS_ERROR("Window couldn't be created!");
		return 1;
	}
	BASE_PROCESS_TRACE("Window created");

	void *main_surface_handle = platif_get_window_surface(main_window_handle);
	if (!main_surface_handle) {
		BASE_PROCESS_ERROR("Couldn't get surface from window");
		return 1;
	}
	BASE_PROCESS_TRACE("Surface created");

	struct window_data *main_window_data = platif_get_window_data(main_window_handle);
	if (!main_window_data) {
		BASE_PROCESS_ERROR("Couldn't create struct window_data");
		return 1;
	}
	BASE_PROCESS_TRACE("Struct window_data created");

	struct pixelbuf *main_pixelbuf = platif_get_surface_pixelbuf(main_surface_handle);
	if (!main_pixelbuf) {
		BASE_PROCESS_ERROR("Couldn't create struct pixelbuf");
		return 1;
	}	
	BASE_PROCESS_TRACE("Struct pixelbuf created");

	struct scaled_pixelbuf *main_spbuf= create_scaled_pixelbuf(SCALING_FACTOR, main_pixelbuf);
	if (!main_spbuf) {
		BASE_PROCESS_ERROR("Scaled pixelbuf couldn't be created!");
		return 1;
	}
	BASE_PROCESS_TRACE("Scaled pixelbuf created");

	// main loop
	SDL_Event event;
	uint8_t keep_going = 1;
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
		if (pixel_counter == main_spbuf->height) {
			pixel_counter = 1;
		} else {
			pixel_counter++;
		}

		if (!update(main_spbuf)) {
			return 1;
		}

		if (!map_spbuf_to_buf(main_pixelbuf, main_spbuf)) {
			return 1;
		}
		platif_render_surface(main_window_handle);

	}
	//SDL_DestroyWindow(main_window_p->window);
	//SDL_Quit();
	platif_quit();

	return 0;
}
