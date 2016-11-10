#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "game.h"
#include "snake.h"

#define DELAY 100000

void drawArena(int width, int height);
void processKeyPress(int key);
void signalHandler(int signalNumber);
void initialiseSignals();

int main(int argc, char *argv[]) {

    initialiseGame();
    initialiseSignals();
    initialiseSnake((getWindowWidth() / 2), (getWindowHeight() / 2));

    mvprintw(0, 1, "Snake In C by Nick Bryan");
    drawArena((getWindowWidth() - 1), (getWindowHeight() - 1));

    while (gameIsRunning()) {
        processKeyPress(getch());
        drawScore();
        moveSnake();
        drawSnake();
        usleep(DELAY);
        addMove();
        refresh();
    }

    clear();
    refresh();
    drawGameEnd();

    deleteSnake();
    endwin();
    return 0;
}

void initialiseSignals() {
    struct sigaction signalAction;
    signalAction.sa_handler = signalHandler;
    signalAction.sa_flags = 0;
    sigemptyset(&signalAction.sa_mask);

    sigaction(SIGTERM, &signalAction, NULL);
    sigaction(SIGINT, &signalAction, NULL);

    signalAction.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &signalAction, NULL);
}

void signalHandler(int signalNumber) {
    if (signalNumber == SIGTERM || signalNumber == SIGINT) {
        endwin();
        refresh();
        deleteSnake();
        exit(EXIT_SUCCESS);
    }
}

void drawArena(int width, int height) {
    for (int x = 0; x <= width; x++) {
        for (int y = 5; y <= height; y++) {
            if (y == 5 || y == height || x == 0 || x == width) {
                mvprintw(y, x, "#");
            }
        }
    }
}

void processKeyPress(int key) {
    switch(key) {
        case KEY_UP:
        case 'w':
            if (direction == DOWN) {
                break;
            }

            direction = UP;
            break;
        case KEY_DOWN:
        case 's':
            if (direction == UP) {
                break;
            }

            direction = DOWN;
            break;
        case KEY_LEFT:
        case 'a':
            if (direction == RIGHT) {
                break;
            }

            direction = LEFT;
            break;
        case KEY_RIGHT:
        case 'd':
            if (direction == LEFT) {
                break;
            }

            direction = RIGHT;
            break;
        case 'q':
            gameOver();
            break;
    }
}