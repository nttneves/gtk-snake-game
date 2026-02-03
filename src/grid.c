#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "snake.h"

bool within_bounds(Grid *g, int x, int y){
  if(x >= g->width || x < 0 || y < 0 || y >= g->height){
    return false;
  } else{
    return true;
  }
}

bool has_snake(Snake *s, int x, int y){
  for(int i = 0; i < s->snakeTailLen; i++){
    if(x == s->snakeTailX[i] && y == s->snakeTailY[i]){
      return true;
    }
  }
  return false;
}