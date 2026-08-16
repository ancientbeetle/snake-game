#include "snake.h"

#ifndef S_APPLE
#define S_APPLE

typedef struct {
    int x;
    int y;
} applemanager;

void spawn_apple(applemanager* a_mgr, snakemanager* s_mgr);
void update_apple(applemanager* a_mgr, snakemanager* s_mgr);
void draw_apple(applemanager* mgr, SDL_Renderer* renderer);

#endif
