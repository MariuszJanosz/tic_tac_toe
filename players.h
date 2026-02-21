#ifndef PLAYERS_H
#define PLAYERS_H

#include "board.h"

#define MAX_NAME_LEN 15

typedef int (*get_move_t)(Board_t*);

typedef struct Player_t {
	char name[MAX_NAME_LEN + 1];
	get_move_t get_move;
} Player_t;

void init_player(Player_t *player, const char *name, get_move_t get_move);

#endif //PLAYERS_H