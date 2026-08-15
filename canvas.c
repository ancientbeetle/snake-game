#include <SDL3/SDL.h>
#include "defs.h"

void draw_canvas(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &grid_rect);
}