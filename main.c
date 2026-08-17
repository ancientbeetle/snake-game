#include "window.h"
#include "snake.h"
#include "ext/tinyfiledialogs/tinyfiledialogs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *score_file;
    score_file = fopen("score.conf", "r");
    if (score_file == NULL) {
        puts("No high score file");
        high_score = 0;
    } else {
        puts("File found");
        char high_score_str[20];
        fgets(high_score_str, 20, score_file);
        high_score = atoi(high_score_str);

        fclose(score_file);
    }

    const char* diff = tinyfd_inputBox("Snake", "Please choose a difficulty (easy, normal, hard)", "normal");
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

    char high_score_str_w[32];
    sprintf(high_score_str_w, "echo %d > score.conf", high_score);
    system(high_score_str_w);

    return 0;
}