// game.h
#ifndef GAME_H
#define GAME_H

#include "player.h"

extern int gravity_state;  // 1 = normal, -1 = inverted
extern char last_message[256];

int roll_dice(void);
void take_turn(Player *player);
void print_board(const Player *p1, const Player *p2, const char *message);

#endif
