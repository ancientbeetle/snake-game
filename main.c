#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static const int game_width = 20;
static const int game_height = 11;

static const int window_width = 640;
static const int window_height = 480;
static const int block_size = 24; // size of every grid block
static const int init_block_x = (window_width - (block_size * game_width)) / 2; // X of the first grid block
static const int init_block_y = (window_height - (block_size * game_height)) / 2; // Y of the first grid block
static const int last_block_x = init_block_x + (block_size * game_width);
static const int last_block_y = init_block_y + (block_size * game_height);

static const float move_rate = 200;

static bool window_should_close = false;

typedef enum {
    parent,
    child
} snaketype;

typedef enum {
    left,
    right,
    up,
    down
} directions;

typedef struct {
    unsigned int x;
    unsigned int y;
    snaketype type;
} snakepart;

typedef struct {
    snakepart* snake;
    int number;
    int direction;
} snakemanager;

void free_snake(snakemanager* mgr) {
    free(mgr->snake);
}

void init_snake(snakemanager* mgr) {
    mgr->number = 5;    // for now ill make snakes be 2 units long, i might standardize this later
    mgr->snake = malloc(sizeof(snakepart) * mgr->number);

    for (int i = 0; i < mgr->number; i++) {
        mgr->snake[i].x = init_block_x;
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
                window_should_close = true;
            } else {
                mgr->snake[0].x -= block_size;
            }
            break;
        case right:
            if (mgr->snake[0].x + block_size >= last_block_x) {
                window_should_close = true;
            } else {
                mgr->snake[0].x += block_size;
            }
            break;
        case up:
            if (mgr->snake[0].y - block_size < init_block_y) {
                window_should_close = true;
            } else {
                mgr->snake[0].y -= block_size;
            }
            break;
        case down:
            if (mgr->snake[0].y + block_size >= last_block_y) {
                window_should_close = true;
            } else {
                mgr->snake[0].y += block_size;
            }
            break;
    }
}

SDL_Window* window;
SDL_Renderer* renderer;

SDL_FRect grid_rect = {(float)init_block_x, (float)init_block_y, (float)block_size * game_width, (float)block_size * game_height};

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return -1;
    }

    window = SDL_CreateWindow("Snake", window_width, window_height, 0);
    renderer = SDL_CreateRenderer(window, 0);

    SDL_SetWindowSurfaceVSync(window, true);

    snakemanager snake;
    init_snake(&snake);

    SDL_FRect snakepart_rect;

    float frame_tick = 0;

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    float delta_time = 0;

    SDL_Event event;
    while (!window_should_close) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    window_should_close = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_UP:
                            snake.direction = up;
                            break;
                        case SDLK_DOWN:
                            snake.direction = down;
                            break;
                        case SDLK_LEFT:
                            snake.direction = left;
                            break;
                        case SDLK_RIGHT:
                            snake.direction = right;
                            break;
                    }
            }
        }

        last = now;
        now = SDL_GetPerformanceCounter();

        delta_time = ((now - last)*1000 / (float)SDL_GetPerformanceFrequency());

        if (frame_tick < move_rate) {
            frame_tick += delta_time;
        } else {
            move_snake(&snake);
            frame_tick = 0;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &grid_rect);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int i = 0; i < snake.number; i++) {
            snakepart_rect = (SDL_FRect){snake.snake[i].x, snake.snake[i].y, block_size, block_size};
            SDL_RenderFillRect(renderer, &snakepart_rect);
        }

        SDL_RenderPresent(renderer);
    }

    free_snake(&snake);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}