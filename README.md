# Snakes & Ladders (C Implementation)

A custom C-language terminal implementation of Snakes & Ladders featuring advanced gameplay mechanics[cite: 8].

## Features

- **Custom Board Mechanics**: Features standard snakes/ladders alongside dynamic **gravity-toggling tiles (G)** and **remove-column tiles (R)**[cite: 8, 9].
- **Bounce Rule**: Players bounce backward from the final tile if their dice roll exceeds the remaining distance[cite: 9].
- **Two-Player CLI**: Interactive turn-based console loop for two players (`P1` and `P2`)[cite: 8, 12].

## Project Structure

- `main.c` - Entry point and main game loop[cite: 12].
- `game.c` / `game.h` - Game logic, dice rolls, turns, and special tile rules[cite: 9, 11].
- `board.c` / `board.h` - Board setup, coordinates, and link configurations[cite: 5, 6].
- `player.h` - Player structure definitions.

## Requirements

- A C compiler (such as GCC / MinGW).

## How to Compile and Run

1. Open your terminal or command prompt inside the project folder.
2. Compile all source files together:
   ```bash
   gcc main.c game.c board.c -o snakes_ladders
