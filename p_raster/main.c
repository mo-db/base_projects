/* standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* modules */
#include "video.h"

/* external libraries */
#include <SDL.h>
#include <SDL_image.h>

int draw(struct Pixsurf* pixsurf)
{
	if (!draw_pixel_grid(pixsurf)) {
		return 0;
	}
	return 1;
}

/* void* load_image(char* file) */
/* { */
/* 	SDL_Surface* image = IMG_Load(file); */
/* 	return NULL; */
/* } */


int main(int argc, char* argv[])
{
	char* image_name;
	if (argc > 1) {
		image_name = argv[1];
	}
	SDL_Surface* image = IMG_Load("/Users/moritz/Repos/base_projects/samsung.jpg");
	if(!image) { printf("image didn't load\n"); }
	printf("Image: widht: %d, height: %d\n", image->w, image->h);
	SDL_Surface *converted = SDL_ConvertSurfaceFormat(
		image, SDL_PIXELFORMAT_RGBA32, 0);
	struct Pixsurf* pixsurf2 = create_new_pixsurf(image->w, image->h, image->pixels);
	if (!pixsurf2) {return 1;}





	// testing
	uint32_t pixel = 0xef5097FF;

	struct Pixsurf* pixsurf = create_new_pixsurf(128, 128, NULL);
	if (!pixsurf) {return 1;}

	if (!draw(pixsurf)) {return 1;}

	FILE* fp = fopen("test.ppm", "w");
	FILE* fp2 = fopen("image.ppm", "w");
	assert(fp);
	assert(fp2);

	
	pixsurf_to_ppm(pixsurf, fp, pixel);
	pixsurf_to_ppm(pixsurf2, fp2, pixel);

	free(pixsurf);
	free(pixsurf2);
	return 0;
}
