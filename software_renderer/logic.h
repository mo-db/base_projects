#ifndef LOGIC_H
#define LOGIC_H

#include <SDL2/SDL.h>
#include "video.h"
#include "debug.h"
#include "objects.h"

int draw_number(struct scaled_pixelbuf *sp_p, int number, Uint32 x_offset, Uint32 y_offset);

/* points x,y values can range from 1 - sp_p->width,sp_p->height
 * that is until a system is implemented that can scale out of bound value
 * down to fit inside the surface
 */

/*
 * this function fills the pixel buffer in a way that it handles the array
 * as if it was ordered like a mathematical coordinate system
 * //TODO: maybe write a seperate function that does this?
*/

int draw_line_simple(struct scaled_pixelbuf *sp_p, struct point p1, struct point p2);

#endif
