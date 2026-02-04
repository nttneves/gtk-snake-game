#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "snake.h"
#include "grid.h"
#include "food.h"

typedef struct {

  Snake snake;
  Grid grid;
  Food food;

  int score;
  bool running;

  int direction; // 1 left, 2 right, 3 up, 4 down

} Game;

void game_init(Game *game);

void game_update(Game *game);

void game_restart(Game *game);

#endif