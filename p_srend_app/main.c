#include <SDL2/SDL.h>
#include "../base/include/libbase.h"
#include "video.h"
#include "graphics.h"
#include "state.h"
#include "stdio.h"
#include "stdint.h"

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

	// init state
	struct State state = {0};
	struct Imgui imgui = {0};

	SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, INIT_WIDTH,
								INIT_HEIGHT, SDL_WINDOW_METAL);
	if (!window) {
		BASE_PROCESS_ERROR("SDL_CreateWindow() null return!");
        return 1;
	}

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	if (!surface) {
		BASE_PROCESS_ERROR("SDL_GetWindowSurface() null return!");
        return 1;
	}

	struct scaled_surface* s_surf = create_scaled_surface(SCALING_FACTOR, surface);
	if (!s_surf) {
		BASE_PROCESS_ERROR("create_scaled_pixelbuf() null return!");
		return 1;
	}

	
	SDL_Event event;
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
					state.mouse_x = event.motion.x;
					state.mouse_y = event.motion.y;
					state.scaled_mouse_x = state.mouse_x / SCALING_FACTOR;
					state.scaled_mouse_y = state.mouse_y / SCALING_FACTOR;
					break;
				case SDL_MOUSEBUTTONDOWN:
					state.mouse_down = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					state.mouse_down = 0;
					break;
			}
		}
		
		//INFO: unstable
		imgui_begin();

		/* if (!update_graphics(s_surf, state)) */
		if (!update_graphics(s_surf))
			return 1;
		/* if (!update_audio(NULL)) */
			/* return 1; */


		//INFO: unstable
		imgui_button(10, 30, ++imgui.id, s_surf);
		printf("mouse pos: %d, %d\n", state.mouse_x, state.mouse_y);
		printf("imgui highlight: %d\n", imgui.highlight);
		printf("imgui active: %d\n", imgui.active);
		printf("imgui id: %d\n", imgui.id);

		if (!map_s_surf_to_surf(surface, s_surf))
			return 1;
		SDL_UpdateWindowSurface(window);

		//INFO: unstable
		imgui_end();
		SDL_Delay(10);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 42;
}
