#include <ncurses.h>
#include "game.h"

static bool running = true;
static int rows, columns = 0;
static int score = 0;
static int moves = 0;

void initialiseGame() {
    initscr();
    raw();
    noecho();
    curs_set(false);
    nodelay(stdscr, true);
    keypad(stdscr, true);

    getmaxyx(stdscr, rows, columns);
}

bool gameIsRunning() {
    return running;
}

void gameOver() {
    running = false;
}

int getWindowWidth() {
    return columns;
}

int getWindowHeight() {
    return rows;
}

void addScore() {
    score++;
}

int getScore() {
    return score;
}

void addMove() {
    moves++;
}

int getMoves() {
    return moves;
}

void drawScore() {
    mvprintw(2, 2, "Score: %d", getScore());
    mvprintw(3, 2, "Moves: %d", getMoves());
}

void drawGameEnd() {
    mvprintw((getWindowHeight() / 2), (getWindowWidth() / 2), "GAME OVER!");
    mvprintw((getWindowHeight() / 2) + 1, (getWindowWidth() / 2), "Score: %d", getScore());
    mvprintw((getWindowHeight() / 2) + 2, (getWindowWidth() / 2), "Moves: %d", getMoves());
    refresh();
    nodelay(stdscr, false);
    getch();
}