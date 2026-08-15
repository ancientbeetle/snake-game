#include <stdbool.h>
#include <SDL3/SDL.h>

#ifndef S_SNAKE
#define S_SNAKE

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
    bool is_dead;
} snakemanager;

void init_snake(snakemanager* mgr);
void move_snake(snakemanager* mgr);
void free_snake(snakemanager* mgr);
void draw_snake(snakemanager *mgr, SDL_Renderer* renderer);

extern const float move_rate;

#endif