#ifndef VIDEO_H 
#define VIDEO_H

#include <stdint.h>
#include <stdio.h>

#define INIT_WIDTH 1280
#define INIT_HEIGHT 720
#define SCALING_FACTOR 4

typedef struct {
    int w;
    int h;
    int n_pixels;
    uint32_t *pixels;
} Pixsurf;

// struct makes sense here, possible padding at end
typedef struct {
	uint8_t r, g, b;
} RGB;

typedef union {
	struct {
		double x, y;
	};
	double data[2];
} V2;

typedef union {
	struct {
		double x, y;
	};
	double data[2];
} P2;

typedef union {
	struct {
		double m11, m12;
		double m21, m22;
	};
	double data[4];
} Matrix_2x2;


// set pixels to NULL if a new buffer should be allocated, free as whole
Pixsurf* create_new_pixsurf(int w, int h, uint32_t* pixels);

// for testing purpose
int draw_grid(Pixsurf* pixsurf);

// netpbm
int pixsurf_to_p3(Pixsurf* pixsurf, char* path);
int pixsurf_to_p6(Pixsurf* pixsurf, char* path);
Pixsurf* p6_to_pixsurf(char* path);

// graphics 2D
int draw_cgrid(Pixsurf* pixsurf);
int drawn_trans_cgrid(int* tmatrix, Pixsurf* pixsurf);

int draw_rect(Pixsurf* pixsurf, P2* pos, int w, int h);

#endif
