/* standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* modules */
#include "video.h"

/* external libraries */


int draw(Pixsurf* pixsurf)
{
	/* P2 p1 = {0, 0}; */
	/* if (!draw_rect(pixsurf, &p1, pixsurf->w-100, pixsurf->h-100)) { */
	/* 	return 0; */
	/* } */

	P2 p2 = {5, 20};
	if (!draw_rect(pixsurf, &p2, 50, 250)) {
		return 0;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	Pixsurf* pixsurf = create_new_pixsurf(1280, 960, NULL);
	if (!pixsurf) {return 1;}
	if (!draw(pixsurf)) { return 1; }
	


	char* in_ppm = "samsung.ppm";
	char* out_ppm = "out.ppm";

	/* Pixsurf* pixsurf = p6_to_pixsurf(in_ppm); */
	/* if (!pixsurf) {return 1;} */


	/* Pixsurf* pixsurf = p6_to_pixsurf(in_ppm); */
	/* if (!pixsurf) {return 1;} */
	/* pixsurf_to_p3(pixsurf, image_p3); */

	pixsurf_to_p6(pixsurf, out_ppm);

	free(pixsurf);
	return 0;
}
