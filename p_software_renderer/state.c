#include <SDL2/SDL.h>
#include "state.h"
#include "logic.h"
#include "video.h"
#include "objects.h"
#include <stdlib.h>

int update(struct scaled_pixelbuf *sp_p)
{
	// draw pixel grid for testing
	for (int j = 0; j < sp_p->height; j += 2) {
		for (int i = 0; i < sp_p->width; i += 2) {
			sp_p->buf[(j*sp_p->width) + i] = 0xFF0000FF;
			sp_p->buf[(j*sp_p->width) + i + 1] = 0xFF00FFFF;
		}
		for (int i = 0; i < sp_p->width; i += 2) {
			sp_p->buf[((j+1)*sp_p->width) + i] = 0xFF00FFFF;
			sp_p->buf[((j+1)*sp_p->width) + i + 1] = 0xFF0000FF;
		}
	}

	// draw white again
	for (int i = 0; i < sp_p->n_pixels; i++) {
		sp_p->buf[i] = 0xFFFFFFFF;
	}

	// INFO: this is just for testing and trying out the renderer,
	//TODO: error handling for draw number
	//int tut = rand();
	//draw_number(sp_p, tut, 5, 7);
	
	// could write simple function create_point() or have other easy assign
	struct point p1;
	p1.x = 1;
	p1.y = 1;
	struct point p2;
	p2.x = sp_p->width;
	p2.y = pixel_counter;


	/* static int testvar = 2; */
	/* p2.x = testvar++; */
	/**/
	/* if (testvar >= 20) { */
	/* 	testvar = p1.x; */
	/* } */

	if (!draw_line_simple(sp_p, p1, p2)) {
		return 0;
	}

	return 1;
}
