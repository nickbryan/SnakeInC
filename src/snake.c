#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"
#include "game.h"

// Can this be a define?
static const int START_SIZE = 5;

static SnakeNode *Snake;
int direction = DOWN;

static SnakeNode* allocateSnakeNode();
static void addFood();

void initialiseSnake(int startX, int startY) {
    SnakeNode *currentSnakeNode;

    for (int i = 0; i < START_SIZE; i++) {
        if (i == 0) {
            currentSnakeNode = Snake = allocateSnakeNode();
        } else {
            currentSnakeNode->nextNode = allocateSnakeNode();
            currentSnakeNode = currentSnakeNode->nextNode;
        }

        currentSnakeNode->x = startX;
        currentSnakeNode->y = startY++;
    }

    currentSnakeNode->nextNode = NULL;

    addFood();
}

void moveSnake() {
    SnakeNode *currentNode = Snake;
    int x, y;

    // Cycle to the end of the list
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }

    currentNode->nextNode = allocateSnakeNode();

    switch (direction) {
        case UP:
            x = currentNode->x;
            y = currentNode->y - 1;
            break;
        case DOWN:
            x = currentNode->x;
            y = currentNode->y + 1;
            break;
        case LEFT:
            x = currentNode->x - 1;
            y = currentNode->y;
            break;
        case RIGHT:
            x = currentNode->x + 1;
            y = currentNode->y;
            break;
    }

    currentNode = currentNode->nextNode;
    currentNode->nextNode = NULL;
    currentNode->x = x;
    currentNode->y = y;

    switch (mvinch(y, x)) {
        case ' ':
            // Go back and remove first node in the list
            currentNode = Snake->nextNode;
            mvaddch(Snake->y, Snake->x, ' ');
            free(Snake);
            Snake = currentNode;
            break;
        case '%':
            mvaddch(currentNode->y, currentNode->x, '%');
            addFood();
            addScore();
            break;
        default:
            gameOver();

    }
}

void drawSnake() {
    SnakeNode *currentNode = Snake;

    while(currentNode != NULL) {
        mvaddch(currentNode->y, currentNode->x, '@');
        currentNode = currentNode->nextNode;
    }
}

void deleteSnake() {
    SnakeNode *snakeNode = Snake;

    while(Snake != NULL) {
        snakeNode = Snake->nextNode;
        free(Snake);
        Snake = snakeNode;
    }
}

SnakeNode* allocateSnakeNode() {
    SnakeNode *snakeNode = malloc(sizeof(SnakeNode));

    if (snakeNode == NULL) {
        // TODO: error here
    }

    return snakeNode;
}

void addFood() {
    int x, y;

    do {
        x = rand() % getWindowWidth() + 1;
        y = rand() % getWindowHeight() + 1;
    } while(mvinch(y, x) != ' ');

    mvaddch(y, x, '%');
}
