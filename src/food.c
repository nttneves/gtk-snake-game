#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "snake.h"
#include "food.h"

void spawn_food(Food *f, Grid *g, Snake *s){
  do{
    f->x = rand() % g->width;
    f->y = rand() % g->height;
  } while (has_snake(s, f->x, f->y));
}