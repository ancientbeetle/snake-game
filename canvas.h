#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#ifndef S_CANVAS
#define S_CANVAS

int init_canvas(SDL_Renderer* renderer);
void free_canvas();
void draw_canvas(SDL_Renderer* renderer);

extern SDL_Texture* canvas_tex;

#endif