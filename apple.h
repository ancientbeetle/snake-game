#include "snake.h"
#include <SDL3/SDL_render.h>

#ifndef S_APPLE
#define S_APPLE

typedef struct {
    int x;
    int y;
    SDL_Texture* tex;
} applemanager;

int init_apple(applemanager* a_mgr, snakemanager* s_mgr, SDL_Renderer* renderer);
void free_apple(applemanager* mgr);
void spawn_apple(applemanager* a_mgr, snakemanager* s_mgr);
void update_apple(applemanager* a_mgr, snakemanager* s_mgr);
void draw_apple(applemanager* mgr, SDL_Renderer* renderer);

#endif
