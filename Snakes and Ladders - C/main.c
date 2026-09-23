// main.c

/*
 * Snakes & Ladders – Custom Version
 * Student: Adeel Raza Sheikh
 * Student ID: 23662814
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "game.h"
#include "player.h"

int main(void) {
    srand((unsigned int)time(NULL));  
    init_board();

    Player p1 = {"P1", 1};
    Player p2 = {"P2", 1};

    Player players[2] = {p1, p2};
    int current_player = 0;

    print_board(&players[0], &players[1], "");

    
    while (players[0].position < BOARD_SIZE && players[1].position < BOARD_SIZE) {
        take_turn(&players[current_player]);
        print_board(&players[0], &players[1], last_message);

        if (players[current_player].position == BOARD_SIZE) break;

        current_player = 1 - current_player;
    }

    printf("%s wins!\n", players[current_player].icon);


    return 0;
}


