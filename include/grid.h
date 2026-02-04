#ifndef GRID_H
#define GRID_H

#include "snake.h"

typedef struct{
  int width;
  int height;
} Grid;

bool within_bounds(Grid *g, int x, int y);
bool has_snake(Snake *s, int x, int y);

#endif