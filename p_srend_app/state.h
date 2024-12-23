#ifndef STATE_H
#define STATE_H

#include "video.h"

// tick duration (deltatime)
/* static const double TARGET_FPS = 60.0; */
/* static const uint64_t TICK_DURATION_MS = (1000*(1.0/TARGET_FPS)); */

struct State {
	int pixel_counter; // change this!
	int mouse_x;
	int mouse_y;
	int scaled_mouse_x;
	int scaled_mouse_y;
	int mouse_down;
};
extern struct State state;

int init_state();
/* int update_graphics(struct scaled_surface *s_surf, struct State *state); */
int update_graphics(struct scaled_surface *s_surf);

#endif
