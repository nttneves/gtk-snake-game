#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game.h"

#define HEIGHT 20
#define WIDTH 20

void game_init(Game *game){

  game->grid.width = WIDTH;
  game->grid.height = HEIGHT;

  game->snake.x = game->grid.width / 2;
  game->snake.y = game->grid.height / 2;

  game->snake.snakeTailLen = 0;

  game->direction = 0;

  game->score = 0;

  game->running = false;

  spawn_food(&game->food, &game->grid, &game->snake);
}

void game_restart(Game *game){
  game_init(game);
}

void game_update(Game *game){

  if(!game->running){
    return;
  }

  move_snake(&game->snake, game->direction);

  if(!within_bounds(&game->grid, game->snake.x, game->snake.y)){
    game->running = false;
    return;
  }

  if(check_collision(&game->snake)){
    game->running = false;
    return;
  }

  if(game->snake.x == game->food.x && game->snake.y == game->food.y){
    grow_snake(&game->snake);

    game->score++;

    spawn_food(&game->food, &game->grid, &game->snake);
  }
}