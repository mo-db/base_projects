#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>
#include "video.h"

/* static struct { */
/* 	Uint64 accum;		// frametime accumulator */
/* 	Uint64 tick_counter; */
/* 	Uint32 per_frame_ticks; */
/* 	Uint64 now;			// timer count of current frame */
/* 	Uint64 last;		// timer count of last frame */
/* 	Uint64 start;		// debug mesuring */
/* 	Uint64 end;			// debug mesuring */
/* 	Uint64 delta_ns;	// frame duration */
/* 	double fps; */
/* } state; */

int update(struct scaled_pixelbuf *sp_p);
int pixel_counter;

#endif
