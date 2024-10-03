#ifndef OBJECTS_H
#define OBJECTS_H

#include <sdl3/sdl.h>

// BIT Digits
#define BD_HEIGHT 7
#define BD_WIDTH 5
#define BD_N 10
#define BD_SPACING 2

// BIT Digits
// External tells the compiler that the var is defined elsewere -> no warning
extern const Uint8 *BIT_DIGITS[BD_N];

// Geometry
struct point {
	int x;
	int y;
};

struct line {
	struct point p1;
	struct point p2;
};

int vec_2[2];
int vec_3[3];

#endif
