#include "window.h"
#include "snake.h"
#include "ext/tinyfiledialogs/tinyfiledialogs.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char* diff = tinyfd_inputBox("Snake", "Please choose a difficulty (easy, normal, hard)", "easy");
    if (!strcmp(diff, "easy")) {
        move_rate = 150;
    }
    if (!strcmp(diff, "normal")) {
        move_rate = 100;
    }
    if (!strcmp(diff, "hard")) {
        move_rate = 60;
    }

    int r = handle_window();
    if (r != 0) {
        return -1;
    }

    char end_message[128];
    sprintf(end_message, "Game over!\n\nScore: %d\nHigh score: %d", score, high_score);

    tinyfd_messageBox("Snake", end_message, "ok", "info", 0);

    return 0;
}