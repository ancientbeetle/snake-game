#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

static const int game_width = 20;
static const int game_height = 11;

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
    mgr->number = 2;    // for now ill make snakes be 2 units long, i might standardize this later
    mgr->snake = malloc(sizeof(snakepart) * mgr->number);

    for (int i = 0; i < mgr->number; i++) {
        mgr->snake[i].x = (int)ceilf(game_width / 2.f);
        mgr->snake[i].y = (int)ceilf(game_height / 2.f);

        if (i == 0) {
            mgr->snake[i].type = parent;
        } else {
            mgr->snake[i].type = child;
        }
    }

    mgr->direction = right;
}

void move_snake(snakemanager* mgr) {
    switch (mgr->direction) {
        case left:
            if (mgr->snake[0].x == 0) {
                free_snake(mgr);
                exit(EXIT_FAILURE);
            } else {
                mgr->snake[0].x -= 1;
            }
            break;
        case right:
            if (mgr->snake[0].x == game_width - 1) {
                free_snake(mgr);
                exit(EXIT_FAILURE);
            } else {
                mgr->snake[0].x += 1;
            }
            break;
        case up:
            if (mgr->snake[0].y == 0) {
                free_snake(mgr);
                exit(EXIT_FAILURE);
            } else {
                mgr->snake[0].y -= 1;
            }
            break;
        case down:
            if (mgr->snake[0].y == game_height - 1) {
                free_snake(mgr);
                exit(EXIT_FAILURE);
            } else {
                mgr->snake[0].y += 1;
            }
            break;
    }

    for (int i = 1; i < mgr->number; i++) {
        mgr->snake[i].x = mgr->snake[i-1].x;
        mgr->snake[i].y = mgr->snake[i-1].y;
    }
}

int main() {
    snakemanager snake;
    init_snake(&snake);

    while (1) {
        usleep(400000);
        move_snake(&snake);

        printf("x: %d, y: %d\n", snake.snake[0].x, snake.snake[0].y);
    }

    free_snake(&snake);

    return 0;
}