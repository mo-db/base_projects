#include "../base/include/libbase.h"
#include "video.h"
#include "objects.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

static int *calculate_bit_digits(int number)
{
	int n_digits = 0;
	for (int i = 1; (number / i) >= 1; i *= 10) {
		n_digits += 1;
	}
	
	// +1 to store size in pos 0 -> slice implementation
	int ary_length = (n_digits + 1);
	int *digits = malloc(sizeof(int) * ary_length);
	if (!digits) {
		BASE_PROCESS_ERROR("Couldn't allocate digits ary");
		return NULL;
	}
	BASE_PROCESS_TRACE("malloc digits ary");
	digits[0] = ary_length;

	for (int i = 1; i < ary_length; i++) {
		if (i >= digits[0]) {
			BASE_PROCESS_ERROR("would be out of bounds, crashing here");
			return NULL;
		}
		digits[i] = number / (int)pow(10, (n_digits - (i)));
		number = number % (digits[i] * (int)pow(10, (n_digits - (i))));
	}
	return digits;
}

int draw_number(struct scaled_surface *s_surf, int number,
				uint32_t x_offset, uint32_t y_offset)
{
	uint32_t offset = (y_offset * s_surf->width) + x_offset;
	uint32_t buffer_pos = offset;

	int *digits = calculate_bit_digits(number);
	if (!digits) {
		return 0;
	}

	// iterate over the digits
	for (int m = 1; m < digits[0]; m++) {

		// write the digit into scaled pixelbuf
		for (int i = 0; i < BD_HEIGHT; i++) {
			for (int j = 0; j < BD_WIDTH; j++) {
				if (BIT_DIGITS[digits[m]][(i * BD_WIDTH) + j] == 1) {
					s_surf->pixels[buffer_pos + j] = 0xFFFF0000;
				} else if (BIT_DIGITS[digits[m]][(i * BD_WIDTH) + j] == 0) {
					;
				} else {
					BASE_PROCESS_ERROR("no bit value in bitmap!");
					return 0;
				}
			}
			buffer_pos += s_surf->width;
		}

		offset += (BD_WIDTH) + BD_SPACING;
		buffer_pos = offset;
	}
	return 1;
}
int draw_pixel_grid(struct scaled_surface *s_surf)
{
	// draw pixel grid for testing
	for (int j = 0; j < s_surf->height; j += 2) {
		for (int i = 0; i < s_surf->width; i += 2) {
			s_surf->pixels[(j*s_surf->width) + i] = 0xFF0000FF;
			s_surf->pixels[(j*s_surf->width) + i + 1] = 0xFF00FFFF;
		}
		for (int i = 0; i < s_surf->width; i += 2) {
			s_surf->pixels[((j+1)*s_surf->width) + i] = 0xFF00FFFF;
			s_surf->pixels[((j+1)*s_surf->width) + i + 1] = 0xFF0000FF;
		}
	}
	return 1;
}

int draw_line_simple(struct scaled_surface *s_surf,
					 struct Point p1, struct Point p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	float m = dy/dx;
	int x, y;
	int plot_value;

	// INFO: I will have to flip the pixelbuffer or better cast it into the form of a math coordsys
	for (x = p1.x; x <= p2.x; x++) {
		y = m * (x - p1.x) + p1.y;
		plot_value = (x - 1) + ((s_surf->height - y) * s_surf->width);

		//TODO: How do i do that???
		//LOG_TRACE("plot_value: %d", 1);

		if (plot_value > s_surf->n_pixels) {
			BASE_PROCESS_ERROR("buffer overflow drawing line!");
			return 0;
		} else {
			s_surf->pixels[plot_value] = 0xFFFF0000;
		}
	}
	return 1;
}

