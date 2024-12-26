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
	struct Pixsurf* pixsurf = create_new_pixsurf(128, 128, NULL);
	if (!pixsurf) {return 1;}

	// also enable this as args
	char* image_in = "samgsung.ppm";
	char* image_out = "output.ppm";





	struct Pixsurf* test_image = ppm_to_pixsurf(fp_in);
	if (!test_image) {return 1;}
	pixsurf_to_ppm(pixsurf, fp_out);

	free(pixsurf);
	return 0;
}
