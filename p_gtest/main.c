#include "../base/include/libbase.h"
#include "video.h"
#include "graphics.h"
#include "imgui.h"
#include "state.h"
#include <SDL2/SDL.h>
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
					state.mouse.x = event.motion.x;
					state.mouse.y = event.motion.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					state.mouse.down = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					state.mouse.down = 0;
					break;
			}
		}

		if (!draw_pixel_grid(s_surf)) {
			return 0;
		}

		// draw white again
		for (int i = 0; i < s_surf->n_pixels; i++) {
			s_surf->pixels[i] = 0xFFFFFFFF;
		}
		
		struct Point test_point;
		test_point.x = s_surf->width/2;
		test_point.y = s_surf->height/2;
		draw_point(s_surf, test_point);

		struct Rect test_rect;
		test_rect.p.x = 5;
		test_rect.p.y = 7;
		test_rect.w = 20;
		test_rect.h = 15;
		draw_rect(s_surf, &test_rect);

		/*
		struct Point p1;
		p1.x = 1;
		p1.y = 1;
		struct Point p2;
		p2.x = s_surf->width;
		//p2.y = pixel_counter;
		p2.y = 30;

		if (!draw_line_simple(s_surf, p1, p2)) {
			return 0;
		}
		*/

		imgui_begin();
		if (!imgui_button(30, 20, 0, s_surf)) {
			return 0;
			printf("error\n");
		}
		print_ginf();
		imgui_end();

		/* seperate */

		if (!map_s_surf_to_surf(surface, s_surf))
			return 1;
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
