#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "players.h"

void init_player(Player_t* player, const char* name, get_move_t get_move) {
	strcpy(player->name, name);
	player->get_move = get_move;
}