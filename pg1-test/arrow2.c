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
	if (direction == point_right) {
		face_right();
	}
	else if (direction == point_left) {
		face_right();turn_around();
	}
	else if (direction == point_up) {
		face_up();
	}
	else {
		face_up(); turn_around();
	}


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
	turn_around();
	face_right();
	
	turn_right();
}
	arrow(point_right);
	arrow(point_left);
	arrow(point_down);
	arrow(30);
	arrow(40);
}
