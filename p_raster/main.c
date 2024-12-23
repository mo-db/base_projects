/* standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "assert.h"

/* additional includes */
#include "video.h"

int draw(struct Pixsurf* pixsurf)
{
	if (!draw_pixel_grid(pixsurf)) {
		return 0;
	}
	return 1;
}


int main(int argc, char* argv[])
{
	// testing
	uint32_t pixel = 0xef5097FF;

	struct Pixsurf* pixsurf = create_new_pixsurf(128, 128, NULL);
	if (!pixsurf) {return 1;}

	if (!draw(pixsurf)) {return 1;}

	FILE* fp = fopen("test.ppm", "w");
	assert(fp);

	
	pixsurf_to_ppm(pixsurf, fp, pixel);

	free(pixsurf);
	return 0;
}
