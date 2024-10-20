#include "video.h"
#include "../base/include/libbase.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


// maybe instead of this allocate whole pb struct dyncamically 
// and also allocate the buf in the same malloc
struct scaled_pixelbuf *create_scaled_pixelbuf(Uint8 scaling_factor,
														struct pixelbuf *buf)
{
	struct scaled_pixelbuf *spbuf= malloc(sizeof(struct scaled_pixelbuf));
	if (!spbuf) {
		BASE_PROCESS_ERROR("Could't malloc struct scaled_pixelbuf!");
		return NULL;
	}
	BASE_PROCESS_TRACE("malloc struct for scaled pixelbuf struct");

    spbuf->scaling_factor = scaling_factor;
    spbuf->width = buf->width / scaling_factor;
    spbuf->height = buf->height / scaling_factor;
    spbuf->n_pixels = spbuf->width * spbuf->height;
	
	spbuf->buf = malloc(spbuf->n_pixels * sizeof(Uint32));
    if (!spbuf->buf) {
		BASE_PROCESS_ERROR("Could't create scaled_pixelbuf buf!");
        return NULL;
    }
	BASE_PROCESS_TRACE("malloc struct for scaled pixelbuf buffer");

	for (int i = 0; i < spbuf->n_pixels; i++) {
		spbuf->buf[i] = 0xFFFFFFFF;
	}
    return spbuf;
}

int map_spbuf_to_buf(struct pixelbuf *buf, struct scaled_pixelbuf *spbuf)
{
	// j = the scaled pixel width, l = how may small pixels in withd
	// k = how many small pixels in height
	int j = 0;
	// the parantheses with init_width are for testing
	for (int i = 0; i < spbuf->n_pixels; i++) {
		for (int k = 0; k < (spbuf->scaling_factor * buf->width); k += buf->width) {
			for (int l = 0; l < spbuf->scaling_factor; l++) {
				buf->buf[j+l+k] = spbuf->buf[i];
			}
		}
		if ((j + spbuf->scaling_factor) % buf->width == 0) {
			// -1 to calculate for the row the program is on the end of
			j += (buf->width * (spbuf->scaling_factor-1));
		}
		j += spbuf->scaling_factor;
	}
	return 1;
}
