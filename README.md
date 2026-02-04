# Snake Tron GTK – Neon Arcade Snake Game in C

This project is a **Tron-inspired Snake game** developed in **C**, featuring  
a complete modular architecture and a futuristic neon graphical interface  
built with **GTK3** and **Cairo rendering**.

The game recreates the classic Snake mechanics while adding:

- **Tron-style grid background**
- **Neon light trail body**
- **Rotating spaceship head sprite**
- **Energy orb fruit collectibles**
- **Score HUD and game over popup**

The goal was not only to implement Snake, but to turn it into a visually  
distinct and portfolio-ready arcade project.


## About the Project

This game was developed as a personal project to practice:

- Low-level programming in **C**
- Real-time game logic design
- GUI development using **GTK3**
- 2D rendering with **Cairo**
- Modular separation between engine and interface

It evolved from a simple Snake prototype into a complete Tron-style game  
with a modern aesthetic and structured codebase.


## Game Description

The gameplay is based on the classic Snake concept:

- The snake moves continuously across a grid  
- The player controls it using the arrow keys  
- Energy orbs (fruit) are collected to grow the trail  
- The game ends if the snake hits:
  - The walls
  - Its own body

The objective is to achieve the highest possible score.


## Features

### Core Gameplay

- Classic Snake movement and growth mechanics  
- Grid-based navigation  
- Wall collision detection  
- Self-collision detection  
- Restart system  
- Score tracking  

### Tron Visual Interface (GTK + Cairo)

- Neon gradient background with Tron-style grid  
- Glow effects and light trail rendering  
- Sprite-based collectibles (energy orb)  
- Rotating spaceship head sprite based on direction  
- Game Over popup with automatic restart  
- Minimal HUD with score bar and quit button  

### Modular Design

The project follows a clean separation of responsibilities:

- Game logic is independent from the UI  
- Rendering is fully handled by the GTK layer  
- Each system lives in its own module:
  - Snake
  - Food spawning
  - Grid bounds
  - Game update loop
  - UI rendering

This structure makes the project easy to extend with new features.


## Project Structure
```
.
├── src/
│   ├── main.c         # Entry point (GTK initialization)
│   ├── ui.c           # Tron graphical interface + rendering
│   ├── game.c         # Game loop and state updates
│   ├── snake.c        # Snake movement, growth, collisions
│   ├── food.c         # Food spawning logic
│   └── grid.c         # Grid bounds and helper utilities
│
├── include/
│   ├── ui.h
│   ├── game.h
│   ├── snake.h
│   ├── food.h
│   └── grid.h
│
├── assets/
│   ├── head.png       # Spaceship snake head sprite
│   └── fruit.png      # Energy orb collectible sprite
│
├── Makefile           # Build automation
└── README.md
```

## How to Run

### Requirements

To compile and run this project you need:

- GCC or Clang  
- GTK3  
- pkg-config  
- Cairo  
- math library (`-lm`)  

### Install Dependencies

#### macOS (Homebrew)

```bash
brew install gtk+3 pkg-config
```

#### Ubuntu / Debian

```bash
sudo apt install libgtk-3-dev pkg-config
```

### Build the Game

This project includes a Makefile for easy compilation:

```bash
make
```

### Run the game

```bash
./snake
```

or directly:

```bash
make run 
```

## Controls

- Arrow Keys → Move the snake  
- R → Restart manually  
- ESC → Quit instantly  
- Quit Button → Exit the game window  


## Results

The final version delivers a complete arcade-style Snake game with:

- Smooth tick-based updates through GTK timers  
- Neon Tron-inspired aesthetics  
- Sprite scaling and rotation support  
- Modular architecture suitable for extension  
- Score HUD and full restart system  

This repository represents a strong portfolio example of a full graphical  
project in C using GTK and Cairo.


## Author

**Nuno Neves**  
