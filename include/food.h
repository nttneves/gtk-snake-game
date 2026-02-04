#ifndef FOOD_H
#define FOOD_H

#include "grid.h"
#include "snake.h"

typedef struct{
  int x;
  int y;
} Food;

void spawn_food(Food *f, Grid *g, Snake *s);

#endif