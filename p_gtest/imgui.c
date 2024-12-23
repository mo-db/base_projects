#include "../base/include/libbase.h"
#include "objects.h"
#include "video.h"
#include "graphics.h"
#include "imgui.h"
#include "state.h"
#include <stdint.h>

static struct Imgui {
	int active;
	int highlight;
	int id;
} imgui;

void imgui_begin()
{
	imgui.highlight = 0;
	imgui.id = 0;
}

/* I'm sure this can be rewritten to be more readable! */
void imgui_end()
{
	/* if button was not down in that frame reset imgui_active */
	if (!state.mouse.down) {
		imgui.active = 0;
	} else if (!imgui.active) { // mouse is down here
		/* deactivate while mouse down but not inside element */
		imgui.active = -1;
	}
}

int imgui_button(int x, int y, int id, struct scaled_surface *s_surf)
{
	const int W = 40;
	const int H = 30;

	//FIX: one s_pixel off
	if (state.mouse.x >= x && (s_surf->height - (state.mouse.y / SCALING_FACTOR)) >= y &&
		state.mouse.x <= (x + W) && (s_surf->height - (state.mouse.y / SCALING_FACTOR)) <= (y + W)) {
		imgui.highlight = id;
		if (imgui.active == 0 && state.mouse.down) {
			imgui.active = id;
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

	if (imgui.highlight == id && imgui.active == id) {
		click_offset_x = 2;
		click_offset_y = 2;
		bg_color = 0xFFFF0000;
	} else if (imgui.active == id) {
		click_offset_x = 2;
		click_offset_y = 2;
		bg_color = 0xAAAA0000;

	} else if (imgui.highlight == id) {
		bg_color = 0xFFFF0000;
	} else { // readabillity bad
		bg_color = 0xAAAA0000;
	}

	if (!new_draw_rect(s_surf, x + SHADOW_OFFSET_X, y + SHADOW_OFFSET_Y, W, H, shadow_color))
		return -1;
	if (!new_draw_rect(s_surf, x + click_offset_x, y + click_offset_y, W, H, bg_color))
		return -1;

	if (imgui.active == id && imgui.highlight == id && !state.mouse.down) {
		return 1;
	} else {
		return 0;
	}
}

void print_ginf() {
	printf("mouse pos: %d, %d\n", state.mouse.x, state.mouse.y);
	printf("imgui highlight: %d\n", imgui.highlight);
	printf("imgui active: %d\n", imgui.active);
	printf("imgui id: %d\n", imgui.id);
}
