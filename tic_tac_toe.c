#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "board.h"
#include "players.h"
#include "human_player.h"
#include "ai_player.h"

int main(int argc, char** argv) {
	srand(time(NULL));
	Board_t board;
	init_board(&board);
	Player_t players[2];
	init_player(&players[0], "Player 1", human_get_move);
	init_player(&players[1], "Player 2", perfect_ai_get_move);
	int player = 0;
	int rnd = 9;
	while (rnd) {
		printf("Turn of %s\n", players[player].name);
		int move = players[player].get_move(&board);
		board.board[(move - 1) / 3][(move - 1) % 3] = player == 0 ? X_ : O_;
		draw_board(&board);
		if (solved(&board)) {
			break;
		}
		player ^= 1;
		--rnd;
	}
	if (rnd) {
		printf("%s won!", players[player].name);
	}
	else {
		printf("It's a tie!");
	}
	return 0;
}
