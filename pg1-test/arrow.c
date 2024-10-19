#include "turtle.h"

void turn_right() {
	rotate(90);
};

void face_right() {
	face_up();
	turn_right();
}

void turn_around() { rotate(180); }

enum {
	point_left,
	point_right,
	point_up,
	point_down
};

void arrow(float degrees) {
	
	rotate(degrees);

	turn_left();
	forward(16.57/2);
	turn_right();

	forward(100);
	turn_left();
	forward(20);
	rotate(3*45);
	forward(40);
	turn_right();
	forward(40);
	rotate(3*45);
	forward(20);
	turn_left();
	forward(100);
	turn_right();
	forward(16.57/2);
	
	turn_right();
	rotate(-degrees);
}

void arrow_strip(float degrees, int count) {
	if (count > 0) {
		arrow(degrees);
		pen_up();rotate(degrees);forward(140);rotate(-degrees);pen_down();
		arrow_strip(degrees, count-1);
	}
}

void run() {
	turn_around();pen_up();forward(300);turn_around();pen_down();
// 	arrow(0);
// 	pen_up();forward(140);pen_down();
// 	arrow(0);
// 	pen_up();forward(140);pen_down();
// 	arrow(0);
// 	pen_up();forward(140);pen_down();
// 	arrow(0);
	arrow_strip(10, 1);
}
