#include "turtle.h"

void turn_right() {
	turn_left();
	turn_left();
	turn_left();
}

void run() {
	/*     
	 *
	 *   011112   34444
	 *   0    2  3
	 *   0    2 3
	 *   0    23
	 *   0
	 *   0
	 *   0
	 *
	 */
	// 0
	turn_left();
	forward(200);
	// 1
	turn_right();
	forward(20);
	// 2
	turn_right();
	forward(90);
	// 3
	rotate(3*-45);
	forward(90*1.41);
	// 4
	rotate(45);
	forward(20*1.41);
	rotate(3*45);
	forward(100*1.41);
	turn_left();
	forward(100*1.41);
	rotate(3*45);
	forward(20*1.41);
	rotate(45);
	forward(90*1.41);
	rotate(3*-45);
	forward(90);
	turn_right();
	forward(20);
}
