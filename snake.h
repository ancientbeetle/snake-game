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
    int x;
    int y;
    snaketype type;
} snakepart;

typedef struct {
    snakepart* snake;
    int number;
    int direction;
    bool is_dead;
    SDL_Texture* tex;
    SDL_Texture* tex_up;
    SDL_Texture* tex_down;
    SDL_Texture* tex_left;
    SDL_Texture* tex_right;
} snakemanager;

int init_snake(snakemanager* mgr, SDL_Renderer* renderer);
void move_snake(snakemanager* mgr);
void free_snake(snakemanager* mgr);
void draw_snake(snakemanager *mgr, SDL_Renderer* renderer);
void expand_snake(snakemanager* mgr);

extern int score;
extern int high_score;

extern const float move_rate;

#endif