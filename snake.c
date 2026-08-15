#include "snake.h"
#include "defs.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

const float move_rate = 200;

SDL_FRect snakepart_rect;

void free_snake(snakemanager* mgr) {
    free(mgr->snake);
}

void init_snake(snakemanager* mgr) {
    mgr->number = 5;    // for now ill make snakes be 2 units long, i might standardize this later
    mgr->snake = malloc(sizeof(snakepart) * mgr->number);
    mgr->is_dead = false;

    for (int i = 0; i < mgr->number; i++) {
        mgr->snake[i].x = init_block_x - block_size * i;
        mgr->snake[i].y = init_block_y;

        if (i == 0) {
            mgr->snake[i].type = parent;
        } else {
            mgr->snake[i].type = child;
        }
    }

    mgr->direction = right;
}

void move_snake(snakemanager* mgr) {
    for (int i = mgr->number-1; i > 0; i--) {
        mgr->snake[i].x = mgr->snake[i-1].x;
        mgr->snake[i].y = mgr->snake[i-1].y;
    }

    switch (mgr->direction) {
        case left:
            if (mgr->snake[0].x - block_size < init_block_x) {
                mgr->is_dead = true;
            } else {
                mgr->snake[0].x -= block_size;
            }
            break;
        case right:
            if (mgr->snake[0].x + block_size >= last_block_x) {
                mgr->is_dead = true;
            } else {
                mgr->snake[0].x += block_size;
            }
            break;
        case up:
            if (mgr->snake[0].y - block_size < init_block_y) {
                mgr->is_dead = true;
            } else {
                mgr->snake[0].y -= block_size;
            }
            break;
        case down:
            if (mgr->snake[0].y + block_size >= last_block_y) {
                mgr->is_dead = true;
            } else {
                mgr->snake[0].y += block_size;
            }
            break;
    }

    for (int i = mgr->number-1; i > 0; i--) {
        if (mgr->snake[i].x == mgr->snake[0].x && mgr->snake[i].y == mgr->snake[0].y) {
            mgr->is_dead = true;
        }
    }
}

void draw_snake(snakemanager *mgr, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < mgr->number; i++) {
        snakepart_rect = (SDL_FRect){mgr->snake[i].x, mgr->snake[i].y, block_size, block_size};
        SDL_RenderFillRect(renderer, &snakepart_rect);
    }
}