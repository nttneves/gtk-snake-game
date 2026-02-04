CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LIBS = `pkg-config --cflags --libs gtk+-3.0` -lm

SRC = src/main.c src/ui.c src/game.c src/snake.c src/food.c src/grid.c
OUT = snake

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)