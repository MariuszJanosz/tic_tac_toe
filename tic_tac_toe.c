#include <stdio.h>

#include "board.h"
#include "players.h"
#include "human_player.h"

int main(int argc, char** argv) {
	Board_t board;
	init_board(&board);
	Player_t players[2];
	init_player(&players[0], "Player 1", human_get_move);
	init_player(&players[1], "Player 2", human_get_move);
	int player = 0;
	while (1) {
		int move = players[player].get_move(&board);
		board.board[(move - 1) / 3][(move - 1) % 3] = player == 0 ? X_ : O_;
		draw_board(&board);
		player ^= 1;
	}
	printf("Hello, World!");
	return 0;
}