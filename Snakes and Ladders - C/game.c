// game.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "board.h"
#include "game.h"

int gravity_state = 1;  // 1 = normal, -1 = inverted
char last_message[256] = "";

int roll_dice(void) {
    return (rand() % 6) + 1;
}

int move_with_bounce(int pos, int roll) {
    int target = pos + roll;
    if (target > BOARD_SIZE) {
        return BOARD_SIZE - (target - BOARD_SIZE);
    }
    return target;
}

int skip_removed_columns(int pos) {
    int original = pos;
    while (pos <= BOARD_SIZE && is_column_removed(cell_to_column(pos))) {
        pos++;
    }
    if (pos > BOARD_SIZE) {
        return BOARD_SIZE;
    }
    if (pos != original) {
        printf("Skipped removed column(s), now at %d\n", pos);
    }
    return pos;
}

int apply_links(int pos) {
    int is_ladder = 0;
    int dest = get_destination(pos, &is_ladder);

    /* No snake or ladder starting here */
    if (dest == 0) {
        /* Might still be a snake tail or ladder top in inverted gravity */
        if (gravity_state == -1) {
            int head = get_snake_head_from_tail(pos);
            if(head) {
                printf("Inverted gravity! Riding snake up to %d\n", head);
                return head;
            }

            int bottom = get_ladder_bottom_from_top(pos);
            if(bottom) {
                printf("Inverted gravity! Sliding down ladder to %d\n", bottom);
                return bottom;
            }
        }
        return pos;
    }

    /* ---------- Normal gravity ---------- */
    if (gravity_state == 1) {
        if (is_ladder) {
            printf("Ladder from %d to %d\n", pos, dest);
        } else {
            printf("Snake from %d to %d\n", pos, dest);
        }
        return dest;
    }
    /* Snake head → no effect */
    return pos;
}

void apply_special_tiles(int pos, char *message, size_t size) {
    // Gravity toggle (G tiles)
    if (gravity_tiles[pos]) {
        gravity_state = -gravity_state;
        snprintf(
            message + strlen(message),
            size - strlen(message),
            " Landed on G-Tile. Gravity is now %s.",
            gravity_state == 1 ? "NORMAL" : "INVERTED"
        );
    }

    // Remove-column tiles (R tiles)
    if (remove_tiles[pos]) {
        int col = cell_to_column(pos);
        if (!is_column_removed(col) && col != 1 && col != GRID_WIDTH) {
            mark_column_removed(col);
            snprintf(
                message + strlen(message),
                size - strlen(message),
                " Landed on R-Tile. Column %d removed.",
                col
            );
        }
    }
}


void wait_for_enter(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void take_turn(Player *player) {
    last_message[0] = '\0';

    printf("%s's turn. Press Enter to roll...\n", player->icon);
    wait_for_enter();  
    
    int roll = roll_dice();
    int start = player->position;
    int pos = move_with_bounce(start, roll);

    snprintf(last_message, sizeof(last_message),"%s rolled %d. Moved from %d to %d.",player->icon, roll, start, pos);

    pos = skip_removed_columns(pos);
    int before_links = pos;
    pos = apply_links(pos);
    if (pos != before_links) {
        snprintf(last_message + strlen(last_message), sizeof(last_message) - strlen(last_message), " Link moved player to %d", pos);
    }

    apply_special_tiles(pos, last_message, sizeof(last_message));

    player->position = pos;

    printf("\n\n\n\n\n\n\n\n\n\n");    
}

void print_board(const Player *p1, const Player *p2, const char *message) {
    printf("               Snakes & Ladders\n");
    printf("==================================================\n");
    printf("Gravity: %s | Removed Columns: ",
           gravity_state == 1 ? "Normal" : "Inverted");

    int any = 0;
    for (int c = 1; c <= GRID_WIDTH; c++) {
        if (removed_columns[c]) {
            printf("%d ", c);
            any = 1;
        }
    }
    if (!any) printf("none");
    printf("\n\n");

    for (int row = GRID_WIDTH; row >= 1; row--) {
        for (int col = 1; col <= GRID_WIDTH; col++) {
            int cell = (row - 1) * GRID_WIDTH + col;

            if (p1->position == cell && p2->position == cell)
                printf("P1&2 ");
            else if (p1->position == cell)
                printf("P1  ");
            else if (p2->position == cell)
                printf("P2  ");
            else if (is_column_removed(col))
                printf("##  ");
            else if (gravity_tiles[cell])
                printf("G   ");
            else if (remove_tiles[cell])
                printf("R   ");
            else if (cell == BOARD_SIZE)
                printf("W   ");
            else
                printf("%2d  ", cell);
        }
        printf("\n");
    }

    printf("\n--------------------------------------------------\n");
    if (message && message[0] != '\0') {
        printf("%s\n", message);
    }


}

