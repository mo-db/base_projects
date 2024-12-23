#include "../base/include/libbase.h"
#include "graphics.h"
#include "objects.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

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
		pixsurf->pixels = (uint32_t*)(pixsurf + sizeof(struct Pixsurf));
	} else {
		pixsurf->pixels = pixels;
	}
	return pixsurf;
}


/* int map_s_surf_to_surf(SDL_Surface *surf, struct scaled_surface *s_surf) */
/* { */
/* 	// j = the scaled pixel width, l = how may small pixels in withd */
/* 	// k = how many small pixels in height */
/* 	int j = 0; */
/* 	// the parantheses with init_width are for testing */
/* 	for (int i = 0; i < s_surf->n_pixels; i++) { */
/* 		// pixels downwards */
/* 		for (int k = 0; k < (SCALING_FACTOR * surf->w); k += surf->w) { */
/* 			// pixels to the right */
/* 			for (int l = 0; l < SCALING_FACTOR; l++) { */
/* 				((uint32_t*)(surf->pixels))[j+l+k] = s_surf->pixels[i]; */
/* 			} */
/* 		} */
/* 		if ((j + SCALING_FACTOR) % surf->w== 0) { */
/* 			// -1 to calculate for the row the program is on the end of */
/* 			j += (surf->w* (SCALING_FACTOR-1)); */
/* 		} */
/* 		j += SCALING_FACTOR; */
/* 	} */
/* 	return 1; */
/* } */





/**/
/* static int map_point_to_surface(struct scaled_surface *s_surf, */
/* 									 const uint32_t pixel_color, struct Point *p) */
/* { */
/* 	int surf_position = (p->x - 1) + ((s_surf->height - p->y) * s_surf->width); */
/* 	if (surf_position > s_surf->n_pixels) { */
/* 		//TODO:maybe dont crash, just exit this function */
/* 		BASE_PROCESS_ERROR("Surface buffer out of bounds!"); */
/* 		return 0; */
/* 	} else { */
/* 		//TODO: check if pixel_color format is correct? */
/* 		s_surf->pixels[surf_position] = pixel_color; */
/* 	} */
/* 	return 1; */
/* } */
/* static int *calculate_bit_digits(int number) */
/* { */
/* 	int n_digits = 0; */
/* 	for (int i = 1; (number / i) >= 1; i *= 10) { */
/* 		n_digits += 1; */
/* 	} */
/**/
/* 	// +1 to store size in pos 0 -> slice implementation */
/* 	int ary_length = (n_digits + 1); */
/* 	int *digits = malloc(sizeof(int) * ary_length); */
/* 	if (!digits) { */
/* 		BASE_PROCESS_ERROR("Couldn't allocate digits ary"); */
/* 		return NULL; */
/* 	} */
/* 	BASE_PROCESS_TRACE("malloc digits ary"); */
/* 	digits[0] = ary_length; */
/**/
/* 	for (int i = 1; i < ary_length; i++) { */
/* 		if (i >= digits[0]) { */
/* 			BASE_PROCESS_ERROR("would be out of bounds, crashing here"); */
/* 			return NULL; */
/* 		} */
/* 		digits[i] = number / (int)pow(10, (n_digits - (i))); */
/* 		number = number % (digits[i] * (int)pow(10, (n_digits - (i)))); */
/* 	} */
/* 	return digits; */
/* } */
/**/
/* int draw_number(struct scaled_surface *s_surf, int number, */
/* 				uint32_t x_offset, uint32_t y_offset) */
/* { */
/* 	uint32_t offset = (y_offset * s_surf->width) + x_offset; */
/* 	uint32_t buffer_pos = offset; */
/**/
/* 	int *digits = calculate_bit_digits(number); */
/* 	if (!digits) { */
/* 		return 0; */
/* 	} */
/**/
/* 	// iterate over the digits */
/* 	for (int m = 1; m < digits[0]; m++) { */
/**/
/* 		// write the digit into scaled pixelbuf */
/* 		for (int i = 0; i < BD_HEIGHT; i++) { */
/* 			for (int j = 0; j < BD_WIDTH; j++) { */
/* 				if (BIT_DIGITS[digits[m]][(i * BD_WIDTH) + j] == 1) { */
/* 					s_surf->pixels[buffer_pos + j] = 0xFFFF0000; */
/* 				} else if (BIT_DIGITS[digits[m]][(i * BD_WIDTH) + j] == 0) { */
/* 					; */
/* 				} else { */
/* 					BASE_PROCESS_ERROR("no bit value in bitmap!"); */
/* 					return 0; */
/* 				} */
/* 			} */
/* 			buffer_pos += s_surf->width; */
/* 		} */
/**/
/* 		offset += (BD_WIDTH) + BD_SPACING; */
/* 		buffer_pos = offset; */
/* 	} */
/* 	return 1; */
/* } */
/* int draw_pixel_grid(struct scaled_surface *s_surf) */
/* { */
/* 	// draw pixel grid for testing */
/* 	for (int j = 0; j < s_surf->height; j += 2) { */
/* 		for (int i = 0; i < s_surf->width; i += 2) { */
/* 			s_surf->pixels[(j*s_surf->width) + i] = 0xFF0000FF; */
/* 			s_surf->pixels[(j*s_surf->width) + i + 1] = 0xFF00FFFF; */
/* 		} */
/* 		for (int i = 0; i < s_surf->width; i += 2) { */
/* 			s_surf->pixels[((j+1)*s_surf->width) + i] = 0xFF00FFFF; */
/* 			s_surf->pixels[((j+1)*s_surf->width) + i + 1] = 0xFF0000FF; */
/* 		} */
/* 	} */
/* 	return 1; */
/* } */
/**/
/* int draw_point(struct scaled_surface *s_surf, struct Point p) */
/* { */
/* 	if (!map_point_to_surface(s_surf, 0xFFFF0000, &p)) { */
/* 		return 0; */
/* 	} */
/* 	return 1; */
/* } */
/**/
/* int draw_line_simple(struct scaled_surface *s_surf, */
/* 					 struct Point p1, struct Point p2) */
/* { */
/* 	float dx = p2.x - p1.x; */
/* 	float dy = p2.y - p1.y; */
/* 	float m = dy/dx; */
/* 	struct Point new_point; */
/**/
/* 	// INFO: I will have to flip the pixelbuffer or better cast it into the form of a math coordsys */
/* 	for (new_point.x = p1.x; new_point.x <= p2.x; new_point.x++) { */
/* 		new_point.y = m * (new_point.x - p1.x) + p1.y; */
/* 		if (!map_point_to_surface(s_surf, 0xFFFF0000, &new_point)) { */
/* 			return 0; */
/* 		} */
/* 	} */
/* 	return 1; */
/* } */
/**/
/* int draw_rect(struct scaled_surface *s_surf, */
/* 					 struct Rect *rect) */
/* { */
/* 	struct Point new_point; */
/* 	for (new_point.y = rect->p.y; new_point.y < (rect->h + rect->p.y); new_point.y++) { */
/* 		for (new_point.x = rect->p.x; new_point.x < (rect->w + rect->p.x); new_point.x++) { */
/* 			if (!map_point_to_surface(s_surf, 0xAFAF0000, &new_point)) { */
/* 				return 0; */
/* 			} */
/* 		} */
/* 	} */
/* 	return 1; */
/* } */
/**/
/* // so here maybe a struct element "rect" should be mallocd and filled and drawn? */
/* int new_draw_rect(struct scaled_surface *s_surf, */
/* 					 int x, int y, int w, int h, uint32_t color) */
/* { */
/* 	struct Point new_point; */
/* 	for (new_point.y = y; new_point.y < (y + h); new_point.y++) { */
/* 		for (new_point.x = x; new_point.x < (x + w); new_point.x++) { */
/* 			if (!map_point_to_surface(s_surf, color, &new_point)) { */
/* 				return 0; */
/* 			} */
/* 		} */
/* 	} */
/* 	return 1; */
/* } */
