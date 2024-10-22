#ifndef STATE_H
#define STATE_H

#include "video.h"

// tick duration (deltatime)
static const double TARGET_FPS = 60.0;
static const uint64_t TICK_DURATION_MS = (1000*(1.0/TARGET_FPS));

/* static struct { */
/* 	uint64_t accum;		// frametime accumulator */
/* 	uint64_t tick_counter; */
/* 	Uint32 per_frame_ticks; */
/* 	uint64_t now;			// timer count of current frame */
/* 	uint64_t last;		// timer count of last frame */
/* 	uint64_t start;		// debug mesuring */
/* 	uint64_t end;			// debug mesuring */
/* 	uint64_t delta_ns;	// frame duration */
/* 	double fps; */
/* } state; */

int update(struct scaled_pixelbuf *sp_p);
int pixel_counter;

#endif
