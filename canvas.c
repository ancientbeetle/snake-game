#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include "defs.h"

SDL_Texture* canvas_tex;

int init_canvas(SDL_Renderer* renderer) {
    canvas_tex = IMG_LoadTexture(renderer, "spr_grass.png");
    if (canvas_tex == NULL) {
        return 0;
    }

    return 1;
}

void free_canvas() {
    SDL_DestroyTexture(canvas_tex);
}

void draw_canvas(SDL_Renderer *renderer) {
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //SDL_RenderFillRect(renderer, &grid_rect);
    SDL_RenderTextureTiled(renderer, canvas_tex, NULL, 1, &grid_rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderRect(renderer, &grid_rect);
}