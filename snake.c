#include "snake.h"
#include "defs.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

const float move_rate = 100;

SDL_FRect snakepart_rect;

int init_snake(snakemanager* mgr, SDL_Renderer* renderer) {
    mgr->number = default_snake_length;
    mgr->snake = malloc(sizeof(snakepart) * mgr->number);
    mgr->is_dead = false;

    for (int i = 0; i < mgr->number; i++) {
        mgr->snake[i].x = init_block_x - block_size * i + spawn_offset_x * block_size;
        mgr->snake[i].y = init_block_y + spawn_offset_y * block_size;

        if (i == 0) {
            mgr->snake[i].type = parent;
        } else {
            mgr->snake[i].type = child;
        }
    }

    mgr->direction = right;

    mgr->tex = IMG_LoadTexture(renderer, "spr_snake_tail.png");
    if (mgr->tex == NULL) {
        puts("Error: missing texture");
        return 0;
    }
    mgr->tex_up = IMG_LoadTexture(renderer, "spr_snake_up.png");
    if (mgr->tex_up == NULL) {
        puts("Error: missing texture");
        SDL_DestroyTexture(mgr->tex);
        return 0;
    }
    mgr->tex_down = IMG_LoadTexture(renderer, "spr_snake_down.png");
    if (mgr->tex_down == NULL) {
        puts("Error: missing texture");
        SDL_DestroyTexture(mgr->tex);
        SDL_DestroyTexture(mgr->tex_up);
        return 0;
    }
    mgr->tex_left = IMG_LoadTexture(renderer, "spr_snake_left.png");
    if (mgr->tex_left == NULL) {
        puts("Error: missing texture");
        SDL_DestroyTexture(mgr->tex);
        SDL_DestroyTexture(mgr->tex_up);
        SDL_DestroyTexture(mgr->tex_down);
        return 0;
    }
    mgr->tex_right = IMG_LoadTexture(renderer, "spr_snake_right.png");
    if (mgr->tex_right == NULL) {
        puts("Error: missing texture");
        SDL_DestroyTexture(mgr->tex);
        SDL_DestroyTexture(mgr->tex_up);
        SDL_DestroyTexture(mgr->tex_left);
        return 0;
    }

    return 1;
}

void free_snake(snakemanager* mgr) {
    free(mgr->snake);
    SDL_DestroyTexture(mgr->tex);
    SDL_DestroyTexture(mgr->tex_up);
    SDL_DestroyTexture(mgr->tex_down);
    SDL_DestroyTexture(mgr->tex_left);
    SDL_DestroyTexture(mgr->tex_right);
}

void expand_snake(snakemanager* mgr) {
    mgr->number++;
    snakepart* _parts = realloc(mgr->snake, sizeof(snakepart) * mgr->number);
    if (_parts == NULL) {
        puts("Warning: allocation failed, player will not grow");
        free(_parts);
        return;
    }
    
    _parts[mgr->number-1].type = child;
    _parts[mgr->number-1].x = _parts[mgr->number-2].x;
    _parts[mgr->number-1].y = _parts[mgr->number-2].y;

    mgr->snake = _parts;
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
    snakepart_rect = (SDL_FRect){mgr->snake[0].x, mgr->snake[0].y, block_size, block_size};
    switch (mgr->direction) {
        case up:
            SDL_RenderTexture(renderer, mgr->tex_up, NULL, &snakepart_rect);
            break;
        case down:
            SDL_RenderTexture(renderer, mgr->tex_down, NULL, &snakepart_rect);
            break;
        case left:
            SDL_RenderTexture(renderer, mgr->tex_left, NULL, &snakepart_rect);
            break;
        case right:
            SDL_RenderTexture(renderer, mgr->tex_right, NULL, &snakepart_rect);
            break;
    }

    for (int i = 1; i < mgr->number; i++) {
        snakepart_rect = (SDL_FRect){mgr->snake[i].x, mgr->snake[i].y, block_size, block_size};
        SDL_RenderTexture(renderer, mgr->tex, NULL, &snakepart_rect);
    }
}