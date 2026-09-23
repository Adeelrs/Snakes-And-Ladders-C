// board.c
#include "board.h"

int ladders[BOARD_SIZE + 1];
int snakes[BOARD_SIZE + 1];
int gravity_tiles[BOARD_SIZE + 1];
int remove_tiles[BOARD_SIZE + 1];
int removed_columns[GRID_WIDTH + 1];

void init_board(void) {
    // clear arrays
    for (int i = 0; i <= BOARD_SIZE; i++) {
        ladders[i] = 0;
        snakes[i] = 0;
        gravity_tiles[i] = 0;
        remove_tiles[i] = 0;
    }
    for (int c = 1; c <= GRID_WIDTH; c++) {
        removed_columns[c] = 0;
    }

    // ladders
    ladders[4]  = 14;
    ladders[9]  = 31;
    ladders[28] = 84;
    ladders[40] = 59;
    ladders[63] = 81;

    // snakes
    snakes[17] = 7;
    snakes[62] = 19;
    snakes[87] = 24;
    snakes[98] = 79;
    snakes[54] = 34;

    // gravity tiles (G)
    gravity_tiles[6]  = 1;
    gravity_tiles[22] = 1;
    gravity_tiles[45] = 1;
    gravity_tiles[66] = 1;
    gravity_tiles[88] = 1;

    // remove-column tiles (R)
    remove_tiles[13] = 1;
    remove_tiles[27] = 1;
    remove_tiles[53] = 1;
    remove_tiles[74] = 1;
    remove_tiles[91] = 1;
}

int cell_to_column(int cell) {
    // returns 1..10
    return ((cell - 1) % GRID_WIDTH) + 1;
}

int is_column_removed(int column) {
    if (column < 1 || column > GRID_WIDTH) return 0;
    return removed_columns[column] != 0;
}

void mark_column_removed(int column) {
    if (column >= 1 && column <= GRID_WIDTH) {
        removed_columns[column] = 1;
    }
}

int get_destination(int cell, int *is_ladder) {
    if (ladders[cell] != 0) {
        *is_ladder = 1;
        return ladders[cell];
    }
    if (snakes[cell] != 0) {
        *is_ladder = 0;
        return snakes[cell];
    }
    *is_ladder = 0;
    return 0;   // no snake/ladder
}

int get_snake_head_from_tail(int tail) {
    for (int i = 1; i <= BOARD_SIZE; i++) {
        if (snakes[i] == tail) {
            return i;
        }
    }
    return 0;
}

int get_ladder_bottom_from_top(int top) {
    for (int i = 1; i <= BOARD_SIZE; i++) {
        if (ladders[i] == top) {
            return i;
        }
    }
    return 0;
}