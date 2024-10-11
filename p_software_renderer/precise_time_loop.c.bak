#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// test a thing

/* #dee TESTING */
#ifdef TESTING
static const double TARGET_FPS = 1.0;
static const Uint64 TICK_DURATION_NS = (1000000000*((1.0/TARGET_FPS)/4.0));
#else
static const double TARGET_FPS = 120.0;
static const Uint64 TICK_DURATION_NS = (1000000000*((1.0/TARGET_FPS)/4.0));
#endif

static struct {
	Uint64 accum;		// frametime accumulator
	Uint64 tick_counter;
	Uint32 per_frame_ticks;
	Uint64 now;			// timer count of current frame
	Uint64 last;		// timer count of last frame
	Uint64 start;		// debug mesuring
	Uint64 end;			// debug mesuring
	Uint64 delta_ns;	// frame duration
	double fps;
} state;

static struct {
	Uint32 width;
	Uint32 height;
	SDL_Window *window;
	SDL_Surface *surface;
	Uint32 surface_pixels_n;
	Uint32 pixels_n;
} window;

static Uint32 *pixel_buffer;
static SDL_Event event;

static void panicAndAbort(const char *title, const char *text)
{/*{{{*/
	fprintf(stderr, "PANIC: %s ... %s\n", title, text);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, text, window.window); // if window exists attach to window
	SDL_Quit(); // It's allways save to call, even if not initialised before!
	exit(1);
}/*}}}*/

static void dbugPrint()
{/*{{{*/
	printf("\n### DEBUG PRINT ###\n");
	printf("delta_ns:	%llu\n", state.delta_ns);
	printf("accu:		%llu\n", state.accum);
	printf("tick_dur:	%llu\n", TICK_DURATION_NS);
	state.fps = (1.0 / ((double)state.delta_ns / 1000000000.0));
	printf("fps:		%.9f\n", state.fps);
	/* printf("last:		%llu\n", state.last); */
	/* printf("now:		%llu\n", state.now); */
}/*}}}*/

static void initWindow()
{
	window.width = 1280; // /4 = 320
	window.height = 960; // /4 = 240
	window.window = SDL_CreateWindow("Window", 640, 480, SDL_WINDOW_METAL);
	if (!window.window) {
		panicAndAbort("Could't create window!", SDL_GetError());
	}

	window.surface = SDL_GetWindowSurface(window.window);
	if (!window.surface) {
		panicAndAbort("Could't fetch surface from window!", SDL_GetError());
	}

	window.pixels_n = window.width * window.height;
	window.surface_pixels_n = window.surface->w * window.surface->h;
	//assert(window.pixels_n == window.surface_pixels_n);
}

static void update()
{
	for (int i = 0; i < (int)(window.surface_pixels_n); i++) {
		pixel_buffer[i] = 0xFF0000FF;
	}

	for (int i = 0; i < 100 && i < (int)(window.surface_pixels_n - (state.tick_counter % window.surface_pixels_n)); i++) {
		if (((state.tick_counter % window.surface_pixels_n) + i) > window.surface_pixels_n) {
			panicAndAbort("Array out of bound acces!", "ERROR");
		} else {
			pixel_buffer[(state.tick_counter % window.surface_pixels_n) + i] = 0xFF00FF00;
		}
	}
}

static void render()
{
	SDL_UpdateWindowSurface(window.window);
	if (state.tick_counter % 100 == 0) {
		dbugPrint();
	}
}

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1) {
		panicAndAbort("SDL_Init error!", SDL_GetError());
	}
	initWindow();

	pixel_buffer = (Uint32*)window.surface->pixels;
	for (int i = 0; i < (int)(window.surface_pixels_n); i++) {
		pixel_buffer[i] = 0xFFFFFFFF;
	}

	// main loop
	Uint8 keep_going = 1;
	state.now = SDL_GetPerformanceCounter();
	while (keep_going) {
		state.last = state.now;
		state.now = SDL_GetPerformanceCounter();
		// PerformanceFrequency: 24.000.000 counts/s - 0.024 counts/ns
		state.delta_ns = (1000000000*(state.now - state.last)) / SDL_GetPerformanceFrequency();
		state.accum += state.delta_ns;
		
		// poll for events 
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				keep_going = 0;
			}
			if (event.type == SDL_EVENT_KEY_DOWN) {
    			if (event.key.key == SDLK_A) {
				}
			}
		}

		while (state.accum > TICK_DURATION_NS) {
			printf("test activation\n");
			update(); // FIXME: graceful errhand
			state.per_frame_ticks++;
			if (state.tick_counter == UINT64_MAX) {
				state.tick_counter = 0;
			} else {
				state.tick_counter++;
			}
			state.accum -= TICK_DURATION_NS;
		}
		SDL_DelayNS(1000);
		render(); // FIXME: graceful errhand
	}
	SDL_DestroyWindow(window.window);
	SDL_Quit();
	return 0;
}
