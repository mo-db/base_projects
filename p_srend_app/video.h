#ifndef VIDEO_H
#define VIDEO_H

#include <SDL2/SDL.h>
#include "../base/include/libbase.h"
#include <stdint.h>

#define INIT_WIDTH 1280
#define INIT_HEIGHT 720
#define SCALING_FACTOR 4

struct scaled_surface {
    int width;
    int height;
    int n_pixels;
    uint32_t *pixels;
};

struct scaled_surface *create_scaled_pixelbuf(uint8_t scaling_factor, SDL_Surface *surf);
//int update_scaled_pixelbuf(struct pixelbuf *buf);

int map_spbuf_to_buf(SDL_Surface *surf, struct scaled_surface *s_surf);

//int destroy_struct_scaled_pixelbuf(struct scaled_pixelbuf *scaled_pb);
//int destroy_struct_pixelbuf(struct pixelbuf *);
//int destroy_struct_window_data(struct window_data *);

#endif
