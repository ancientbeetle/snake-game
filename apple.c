#include "apple.h"
#include "snake.h"
#include "defs.h"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdlib.h>

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &apple_rect);
}