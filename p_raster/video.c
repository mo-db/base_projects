/* standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "assert.h"

/* additional includes */
#include "video.h"

struct Pixsurf* create_new_pixsurf(int w, int h, uint32_t* pixels)
{
	struct Pixsurf* pixsurf = NULL;

 	// if no buffer provided, allocate space for it
	if (!pixels) {
		pixsurf = malloc(sizeof(struct Pixsurf) + (w * h * sizeof(uint32_t)));
	} else {
		pixsurf = malloc(sizeof(struct Pixsurf));
	}
	if (!pixsurf) {
		fprintf(stderr, "malloc error\n");
		return pixsurf;
	}

	pixsurf->w = w;
	pixsurf->h = h;
	pixsurf->n_pixels = w * h;

	// if no buffer provided point to space after the Pixsurf struct
	if (!pixels) {
		pixsurf->pixels = (uint32_t*)(pixsurf + 1); // move the pointer to after the struct
	} else {
		pixsurf->pixels = pixels;
	}
	return pixsurf;
}

int draw_grid(struct Pixsurf* pixsurf)
{
	// draw pixel grid for testing
	for (int j = 0; j < pixsurf->h; j += 2) {
		for (int i = 0; i < pixsurf->w; i += 2) {
			pixsurf->pixels[(j*pixsurf->w) + i] = 0xFF0000FF;
			pixsurf->pixels[(j*pixsurf->w) + i + 1] = 0xFF00FFFF;
		}
		for (int i = 0; i < pixsurf->w; i += 2) {
			pixsurf->pixels[((j+1)*pixsurf->w) + i] = 0xFF00FFFF;
			pixsurf->pixels[((j+1)*pixsurf->w) + i + 1] = 0xFF0000FF;
		}
	}
	return 1;
}

int pixsurf_to_ppm(struct Pixsurf* pixsurf, char* path)
{
	FILE* image = fopen(path, "w");
	assert(image);
	// create the ppm header
	fprintf(image, "P3\n");
	fprintf(image, "%d %d\n", pixsurf->w, pixsurf->h);
	fprintf(image, "255\n");

	// convert uint32_t rgba pixelformat to r, g, b respectively
	uint8_t red, green, blue;
	uint32_t pixel_color;
	/* for (int i = 0; i < pixsurf->n_pixels; i++) { */
	for (int i = 0; i < 20; i++) {
		pixel_color = pixsurf->pixels[i];
		red = (pixel_color & 0xFF000000) >> 24;
		green = (pixel_color & 0x00FF0000) >> 16;
		blue = (pixel_color & 0x0000FF00) >> 8;
		fprintf(image, "%d %d %d\n", red, green, blue);
	}
	fclose(image);
	return 1;
}

int ppm_to_pixsurf(char* path)
{
	FILE* image = fopen(path, "r");
	assert(image);

	fclose(image);
	return 1;
}
