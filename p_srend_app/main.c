#include <SDL2/SDL.h>
#include "../base/include/libbase.h"
#include "video.h"
#include "graphics.h"
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

// GUI stuff, move to seperate file later
static int imgui_active;
static int imgui_highlight;
static int imgui_id;

void imgui_begin()
{
	/* int mouse_x = x; */
	/* int mouse_y = y; */
	/* int mouse_down = down; */
	imgui_highlight = 0;
	imgui_id = 0;
}

/* I'm sure this can be rewritten to be more readable! */
void imgui_end()
{
	/* if button was not down in that frame reset imgui_active */
	if (!mouse_down) {
		imgui_active = 0;
	} else if (!imgui_active) { // mouse is down here
		/* deactivate while mouse down but not inside element */
		imgui_active = -1;
	}
}

int imgui_button(int x, int y, int id, struct scaled_surface *s_surf)
{
	const int W = 40;
	const int H = 30;

	//FIX: one s_pixel off
	int s_mouse_x = mouse_x/SCALING_FACTOR;
	int s_mouse_y = s_surf->height - (mouse_y/SCALING_FACTOR);

	if (s_mouse_x >= x && s_mouse_y >= y &&
		s_mouse_x <= (x + W) && s_mouse_y <= (y + W)) {
		imgui_highlight = id;
		if (imgui_active == 0 && mouse_down) {
			imgui_active = id;
		}
	}

	const int CENTER_X = x + W/2;
	const int CENTER_Y = y + H/2;
	const int SHADOW_OFFSET_X = -2;
	const int SHADOW_OFFSET_Y = -2;

	int click_offset_x = 0;
	int click_offset_y = 0;
	int bg_color = 0x0;
	int shadow_color = 0x0;

	if (imgui_highlight == id && imgui_active == id) {
		click_offset_x = 2;
		click_offset_y = 2;
		bg_color = 0xFFFF0000;
	} else if (imgui_active == id) {
		click_offset_x = 2;
		click_offset_y = 2;
		bg_color = 0xAAAA0000;

	} else if (imgui_highlight == id) {
		bg_color = 0xFFFF0000;
	} else { // readabillity bad
		bg_color = 0xAAAA0000;
	}

	if (!new_draw_rect(s_surf, x + SHADOW_OFFSET_X, y + SHADOW_OFFSET_Y, W, H, shadow_color))
		return -1;
	if (!new_draw_rect(s_surf, x + click_offset_x, y + click_offset_y, W, H, bg_color))
		return -1;

	if (imgui_active == id && imgui_highlight == id && !mouse_down) {
		return 1;
	} else {
		return 0;
	}
}

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
					mouse_y = event.motion.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouse_down = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					mouse_down = 0;
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
		imgui_button(10, 30, ++imgui_id, s_surf);
		printf("mouse pos: %d, %d\n", mouse_x, mouse_y);
		printf("imgui highlight: %d\n", imgui_highlight);
		printf("imgui active: %d\n", imgui_active);
		printf("imgui id: %d\n", imgui_id);

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
