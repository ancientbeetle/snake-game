#include "apple.h"
#include "snake.h"
#include "defs.h"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int init_apple(applemanager *a_mgr, snakemanager *s_mgr, SDL_Renderer* renderer) {
    a_mgr->tex = IMG_LoadTexture(renderer, "spr_apple.png");
    if (a_mgr->tex == NULL) {
        puts("Error: missing texture");
        SDL_DestroyTexture(a_mgr->tex);
        return 0;
    }
    spawn_apple(a_mgr, s_mgr);

    return 1;
}

void free_apple(applemanager *mgr) {
    SDL_DestroyTexture(mgr->tex);
}

void spawn_apple(applemanager* a_mgr, snakemanager* s_mgr) {
    int temp_x = init_block_x + block_size * (rand() % canvas_width);
    int temp_y = init_block_y + block_size * (rand() % canvas_height);

    for (int i = 0; i < s_mgr->number; i++) {
        if (s_mgr->snake[i].x == temp_x && s_mgr->snake[i].y == temp_y) {
            spawn_apple(a_mgr, s_mgr);
            return;
        }
    }

    a_mgr->x = temp_x;
    a_mgr->y = temp_y;
}

void update_apple(applemanager* a_mgr, snakemanager* s_mgr) {
    if (s_mgr->snake[0].x == a_mgr->x && s_mgr->snake[0].y == a_mgr->y) {
        spawn_apple(a_mgr, s_mgr);
        expand_snake(s_mgr);
    }
}

void draw_apple(applemanager* mgr, SDL_Renderer* renderer) {
    const SDL_FRect apple_rect = {mgr->x, mgr->y, block_size, block_size};
    SDL_RenderTexture(renderer, mgr->tex, NULL, &apple_rect);
}