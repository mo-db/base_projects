#ifndef STATE_H
#define STATE_H

#include "video.h"

// tick duration (deltatime)
static const double TARGET_FPS = 60.0;
static const uint64_t TICK_DURATION_MS = (1000*(1.0/TARGET_FPS));

struct State {
	int pixel_counter; // change this!
};
extern struct State state;

int init_state();
/* int update_graphics(struct scaled_surface *s_surf, struct State *state); */
int update_graphics(struct scaled_surface *s_surf);

#endif
