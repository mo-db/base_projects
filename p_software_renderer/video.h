#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include "../base/include/libbase.h"

struct window_data {
	int width;
	int height;
};

struct pixelbuf {
	int width;
	int height;
	int n_pixels;
	uint32_t *buf;
};

struct scaled_pixelbuf {
    int width;
    int height;
    int n_pixels;
    uint8_t scaling_factor;
    uint32_t *buf;
};

struct scaled_pixelbuf *create_scaled_pixelbuf(uint8_t scaling_factor, struct pixelbuf *pb);
//int update_scaled_pixelbuf(struct pixelbuf *buf);

int map_spbuf_to_buf(struct pixelbuf *buf, struct scaled_pixelbuf *spbuf);

//int destroy_struct_scaled_pixelbuf(struct scaled_pixelbuf *scaled_pb);
//int destroy_struct_pixelbuf(struct pixelbuf *);
//int destroy_struct_window_data(struct window_data *);

#endif
