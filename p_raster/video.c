/* standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "assert.h"

/* additional includes */
#include "video.h"
#include "ctype.h"
#include "string.h"

Pixsurf* create_new_pixsurf(int w, int h, uint32_t* pixels)
{
	Pixsurf* pixsurf = NULL;

 	// if no buffer provided, allocate space for it
	if (!pixels) {
		pixsurf = malloc(sizeof(Pixsurf) + (w * h * sizeof(uint32_t)));
	} else {
		pixsurf = malloc(sizeof(Pixsurf));
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

static int fill_segmetn(Pixsurf* pixsurf, uint32_t rgba_value, P2* p, int len)
{
	/* int index = (p->x - 1) + ((pixsurf->h - p->y) * pixsurf->w); */

	int index = (p->x - 1) + (p->y * pixsurf->w);
	if ((index + len) > pixsurf->n_pixels) {
		printf("err: out of bounds!\n");
		return 0;
	} else {
		for (int i = 0; i < len; i++) {
			pixsurf->pixels[index + i] = rgba_value;
		}
	}
	return 1;
}

static int fill_point(Pixsurf* pixsurf, uint32_t rgba_value, P2* p)
{
	int index = (p->x - 1) + ((pixsurf->h - p->y) * pixsurf->w);
	if (index > pixsurf->n_pixels) {
		printf("err: out of bounds!\n");
		return 0;
	} else {
		pixsurf->pixels[index] = rgba_value;
	}
	return 1;
}

int draw_grid(Pixsurf* pixsurf)
{
	// draw pixel grid for testing
	for (int j = 0; j < pixsurf->h; j += 2) {
		for (int i = 0; i < pixsurf->w; i += 2) {
			pixsurf->pixels[(j*pixsurf->w) + i] = 0xFF0000FF;
			pixsurf->pixels[(j*pixsurf->w) + i + 1] = 0x00FF00FF;
		}
		for (int i = 0; i < pixsurf->w; i += 2) {
			pixsurf->pixels[((j+1)*pixsurf->w) + i] = 0x00FF00FF;
			pixsurf->pixels[((j+1)*pixsurf->w) + i + 1] = 0xFF0000FF;
		}
	}
	return 1;
}

// convert 32bit rgba value into 3x1bit rgb matrix
// TODO: do I need error handling in functions like this one?
static void rgba32_to_rgb_matrix(uint32_t pixcolor, RGB* rgb_matrix)
{
	rgb_matrix->r = (pixcolor & 0xFF000000) >> 24; 	// red
	rgb_matrix->g = (pixcolor & 0x00FF0000) >> 16; 	// green
	rgb_matrix->b = (pixcolor & 0x0000FF00) >> 8; 	// blue
}

static void rgb_matrix_to_rgba32(uint32_t* pixcolor, RGB* rgb_matrix)
{
	*pixcolor = ((rgb_matrix->r << 24) & 0xFF000000)
		+ ((rgb_matrix->g << 16) & 0x00FF0000)
		+ ((rgb_matrix->b << 8) & 0x0000FF00);
}

// TODO: fix precision issue
static void rgb_matrix_to_yiq_matrix(uint8_t* rgb_matrix, uint8_t* yiq_matrix)
{
	float bp[] = {
		0.299, 0.587, 0.114, 
		0.5959, -0.2746, -0.3213,
		0.2115, -0.5227, -0.3112
	};
	yiq_matrix[0] = bp[0]*rgb_matrix[0] + bp[1]*rgb_matrix[1] + bp[2]*rgb_matrix[2];
	yiq_matrix[1] = bp[3]*rgb_matrix[0] + bp[4]*rgb_matrix[1] + bp[5]*rgb_matrix[2];
	yiq_matrix[2] = bp[6]*rgb_matrix[0] + bp[7]*rgb_matrix[1] + bp[8]*rgb_matrix[2];
}

// TODO: fix precision issue
static void yiq_matrix_to_rgb_matrix(uint8_t* rgb_matrix, uint8_t* yiq_matrix)
{
	float bp[] = {
		1, 0.956, 0.619,
		1, -0.272, -0.647,
		1, -1.106, 1.703
	};
	rgb_matrix[0] = bp[0]*yiq_matrix[0] + bp[1]*yiq_matrix[1] + bp[2]*yiq_matrix[2];
	rgb_matrix[1] = bp[3]*yiq_matrix[0] + bp[4]*yiq_matrix[1] + bp[5]*yiq_matrix[2];
	rgb_matrix[2] = bp[6]*yiq_matrix[0] + bp[7]*yiq_matrix[1] + bp[8]*yiq_matrix[2];

}

int draw_rect(Pixsurf* pixsurf, P2* p, int w, int h)
{
	uint32_t rgba_val;
	P2 new_p;
	int count = 0;

	RGB rgb_matrix;

	for (new_p.y = p->y; new_p.y < (p->y + h); new_p.y++) {
 		rgb_matrix = (RGB){count % 255, count % 5, count % 255};
		/* rgb_matrix_to_rgba32(&rgba_val, &(RGB){count % 255, count % 255, count % 255}); */
		rgb_matrix_to_rgba32(&rgba_val, &rgb_matrix);
		if(!fill_segmetn(pixsurf, rgba_val, &new_p, w)) { return 0; }
		count++;
	}
	return 1;
}


int pixsurf_to_p3(Pixsurf* pixsurf, char* path)
{
	FILE* image = fopen(path, "w");
	assert(image);

	// ppm P3 header
	fprintf(image, "P3\n%d %d\n255\n", pixsurf->w, pixsurf->h);

	RGB rgb_matrix;
	for (int i = 0; i < pixsurf->n_pixels; i++) {
		rgba32_to_rgb_matrix(pixsurf->pixels[i], &rgb_matrix);
		fprintf(image, "%d %d %d\n", rgb_matrix.r, rgb_matrix.g, rgb_matrix.b);
	}

	fclose(image);
	return 1;
}

int pixsurf_to_p6(Pixsurf* pixsurf, char* path)
{
	FILE* image = fopen(path, "wb");
	assert(image);

	// ppm P6 header
	fprintf(image, "P6\n%d %d\n255\n", pixsurf->w, pixsurf->h);

	RGB color;
	for (int i = 0; i < pixsurf->n_pixels; i++) {
		rgba32_to_rgb_matrix(pixsurf->pixels[i], &color);
		fwrite(&color, sizeof color.r, 3, image);
	}

	fclose(image);
	return 1;
}

Pixsurf* p6_to_pixsurf(char* path)
{
	FILE* image = fopen(path, "rb");
	assert(image);

	const char* MAGIC_ID = "P6";
	char buf[10];
	uint32_t w;
	uint32_t h;
	uint32_t max;

	char c;
	int arg_count = 0;
	int buf_count = 0;
	printf("\nPPM Header: \n"); // INFO: debug
	while (1) {
		c = fgetc(image);

		// ppm supports comments, skip over those
		if (c == '#') { 
			while ((c = fgetc(image)) != '\n') { /* do nothing */ }
			c = fgetc(image);
		}

		// cases for the 4 header parts
		if (isspace(c)) {
			buf[buf_count] = '\0';
			printf("%d: %s\n", arg_count, buf); // INFO: debug
			if (arg_count == 0) {
				if (strcmp(buf, MAGIC_ID) != 0) {
					printf("err: magic id does not compare\n");
					return NULL;
				}
			} else if (arg_count == 1) {
				w = atoi(buf);
			} else if (arg_count == 2) {
				h = atoi(buf);
			} else if (arg_count == 3) {
				if (strcmp(buf, "255") != 0) {
					printf("err: end of header not found (max color value)\n");
					return NULL;
				} else { break; }
			}
			buf_count = 0;
			arg_count++;
		} else {
			buf[buf_count++] = c;
		}
	}
	
	// allocate new pixsurf struct and pixel buffer
	Pixsurf* pixsurf = create_new_pixsurf(w, h, NULL);
	if (!pixsurf) {return NULL;}

	// fill pixsurf, TODO: to many fread? Can i first save to buffer or something?
	RGB color;
	for (int i = 0; i < pixsurf->n_pixels; i++) {
		fread(&color, sizeof color.r, 3, image);  // sizeof element, prevent padding
		rgb_matrix_to_rgba32(pixsurf->pixels+i, &color);
	}

	fclose(image);
	return pixsurf;
}
