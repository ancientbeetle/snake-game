#include "window.h"
#include "snake.h"
#include "ext/tinyfiledialogs/tinyfiledialogs.h"
#include <stdio.h>
int main() {

    int r = handle_window();
    if (r != 0) {
        return -1;
    }

    char end_message[128];
    sprintf(end_message, "Game over!\n\nScore: %d\nHigh score: %d", score, high_score);

    tinyfd_messageBox("Snake", end_message, "ok", "info", 0);

    return 0;
}