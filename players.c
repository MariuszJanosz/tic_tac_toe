#include <stdlib.h>
#include <stdio.h>

#include "players.h"

void init_player(Player_t* player, const char* name, get_move_t get_move) {
	if (strlen(name) > MAX_NAME_LEN) {
		fprintf(stderr, "Name is to long\n");
		exit(1);
	}
	strcpy(player->name, name);
	player->get_move = get_move;
}