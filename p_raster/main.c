/* standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* modules */
#include "video.h"

/* external libraries */


int draw(struct Pixsurf* pixsurf)
{
	if (!draw_grid(pixsurf)) {
		return 0;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	/* struct Pixsurf* pixsurf = create_new_pixsurf(640, 853, NULL); */
	/* if (!pixsurf) {return 1;} */

	// also enable this as args
	char* image_in = "samsung.ppm";
	char* image_p3 = "p3.ppm";
	char* image_p6 = "p6.ppm";

	/* draw_grid(pixsurf); */

	/* struct Pixsurf* test_image = ppm_to_pixsurf(image_in); */
	/* if (!test_image) {return 1;} */
	
	// this one should return pixsurf of correct size
	struct Pixsurf* pixsurf = p6_to_pixsurf(image_in);
	if (!pixsurf) {return 1;}
	/* pixsurf_to_p3(pixsurf, image_p3); */
	pixsurf_to_p6(pixsurf, image_p6);

	free(pixsurf);
	return 0;
}
