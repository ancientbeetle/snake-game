#include "window.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "defs.h"
#include "snake.h"
#include "apple.h"
#include "canvas.h"

#include <stdio.h>

bool window_should_close = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void destroy_all() {
    window_should_close = true;
}

int main() {
    srand(time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return -1;
    }

    window = SDL_CreateWindow("Snake", window_width, window_height, 0);
    if (window == NULL) {
        puts("Error: unable to create window");
        SDL_Quit();
        return -1;
    }
    renderer = SDL_CreateRenderer(window, 0);
    if (renderer == NULL) {
        puts("Error: unable to create renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_SetWindowSurfaceVSync(window, true);

    snakemanager snake;
    applemanager apple;
    int t = init_snake(&snake, renderer);
    if (t == false) {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return -1;
    }

    t = init_apple(&apple, &snake, renderer);
    if (t == false) {
        free_snake(&snake);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return -1;
    }

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
                            if (snake.direction != down)
                                snake.direction = up;
                            break;
                        case SDLK_DOWN:
                            if (snake.direction != up)
                                snake.direction = down;
                            break;
                        case SDLK_LEFT:
                            if (snake.direction != right)
                                snake.direction = left;
                            break;
                        case SDLK_RIGHT:
                            if (snake.direction != left)
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
            update_apple(&apple, &snake);
            frame_tick = 0;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        draw_canvas(renderer);
        draw_snake(&snake, renderer);
        draw_apple(&apple, renderer);

        if (snake.is_dead) {
            window_should_close = true;
        }

        SDL_RenderPresent(renderer);
    }

    free_snake(&snake);
    free_apple(&apple);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}