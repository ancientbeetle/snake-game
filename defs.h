#include <SDL3/SDL.h>

#ifndef S_DEFS
#define S_DEFS

extern const int window_width;
extern const int window_height;

extern bool window_should_close;

extern const int canvas_width;
extern const int canvas_height;

extern const int block_size;

extern const int init_block_x;
extern const int init_block_y;
extern const int last_block_x;
extern const int last_block_y;

extern SDL_FRect grid_rect;

#endif