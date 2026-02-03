#ifndef SNAKE_H
#define SNAKE_H

typedef struct{
  // Array to store the coordinates of snake
  // tail (x-axis, y-axis)
  int snakeTailX[100], snakeTailY[100];

  // Variable to store the length of the
  // snake's tail
  int snakeTailLen;

  // Coordinates of snake's head
  int x, y;
} Snake;

void move_snake(Snake *s, int key);
void grow_snake(Snake *s);
bool check_collision(Snake *s);

#endif