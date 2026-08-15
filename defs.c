#include <SDL3/SDL.h>

const int window_width = 640;
const int window_height = 480;

const int canvas_width = 20;
const int canvas_height = 11;

const int block_size = 24; // size of every grid block
const int init_block_x = (window_width - (block_size * canvas_width)) / 2; // X of the first grid block
const int init_block_y = (window_height - (block_size * canvas_height)) / 2; // Y of the first grid block
const int last_block_x = init_block_x + (block_size * canvas_width);
const int last_block_y = init_block_y + (block_size * canvas_height);

SDL_FRect grid_rect = {(float)init_block_x, (float)init_block_y, (float)block_size * canvas_width, (float)block_size * canvas_height};