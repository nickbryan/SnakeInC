#ifndef SNAKETERM_GAME_H
#define SNAKETERM_GAME_H

#include <stdbool.h>

static bool running;
static int rows, columns;
static int score;

void initialiseGame();
bool gameIsRunning();
void gameOver();
int getWindowWidth();
int getWindowHeight();
void addScore();
int getScore();
void addMove();
int getMoves();
void drawScore();
void drawGameEnd();

#endif
