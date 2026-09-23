// board.h
#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 100
#define GRID_WIDTH 10

// arrays indexed 0..BOARD_SIZE (we’ll ignore index 0)
extern int ladders[BOARD_SIZE + 1];
extern int snakes[BOARD_SIZE + 1];
extern int gravity_tiles[BOARD_SIZE + 1];
extern int remove_tiles[BOARD_SIZE + 1];

// 1..GRID_WIDTH (1–10), 1 means removed, 0 means active
extern int removed_columns[GRID_WIDTH + 1];

// ---- function declarations (VERY IMPORTANT) ----
void init_board(void);
int cell_to_column(int cell);
int is_column_removed(int column);
void mark_column_removed(int column);
int get_destination(int cell, int *is_ladder);
int get_snake_head_from_tail(int tail);
int get_ladder_bottom_from_top(int top);

#endif
