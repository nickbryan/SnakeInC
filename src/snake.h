#ifndef SNAKETERM_SNAKE_H
#define SNAKETERM_SNAKE_H

typedef struct snake_node {
    int x;
    int y;
    struct snake_node *nextNode;
} SnakeNode;

enum direction_type {UP, DOWN, LEFT, RIGHT};
extern int direction;

void initialiseSnake(int startX, int startY);
void drawSnake();
void moveSnake();
void deleteSnake();

#endif
