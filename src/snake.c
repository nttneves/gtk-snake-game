#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "snake.h"

void move_snake(Snake *s, int key){

  int prevX = s->snakeTailX[0];
  int prevY = s->snakeTailY[0];
  int prev2X, prev2Y;
  s->snakeTailX[0] = s->x;
  s->snakeTailY[0] = s->y;

  for (int i = 1; i < s->snakeTailLen; i++){
    prev2X = s->snakeTailX[i];
    prev2Y = s->snakeTailY[i];
    s->snakeTailX[i] = prevX;
    s->snakeTailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  switch (key){
  case 1:
    s->x--;
    break;
  case 2:
    s->x++;
    break;
  case 3:
    s->y--;
    break;
  case 4:
    s->y++;
    break;
  default:
    break;
  }
}

void grow_snake(Snake *s){

  if (s->snakeTailLen >= 100)
    return;

  if (s->snakeTailLen == 0){

    s->snakeTailX[0] = s->x;
    s->snakeTailY[0] = s->y;
    s->snakeTailLen = 1;
    return;
  }

  int lastX = s->snakeTailX[s->snakeTailLen - 1];
  int lastY = s->snakeTailY[s->snakeTailLen - 1];

  s->snakeTailX[s->snakeTailLen] = lastX;
  s->snakeTailY[s->snakeTailLen] = lastY;

  s->snakeTailLen++;
}

bool check_collision(Snake *s){

  for (int k = 1; k < s->snakeTailLen; k++){
    if (s->x == s->snakeTailX[k] && s->y == s->snakeTailY[k]){
      return true;
    }
  }

  return false;
}