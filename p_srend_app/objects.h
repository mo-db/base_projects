#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>

// BIT Digits
#define BD_HEIGHT 7
#define BD_WIDTH 5
#define BD_N 10
#define BD_SPACING 2

// BIT Digits
// External tells the compiler that the var is defined elsewere -> no warning
extern const uint8_t *BIT_DIGITS[BD_N];

// Geometry
struct Point {
	int x;
	int y;
};

struct Line {
	struct Point p1;
	struct Point p2;
};

struct Rect {
	struct Point p;
	int w;
	int h;
};

#endif
