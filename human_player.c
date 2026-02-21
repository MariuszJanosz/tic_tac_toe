#include <stdio.h>

#include "human_player.h"
#include "board.h"
#include "players.h"

int human_get_move(Board_t* board) {
	int move;
	while (1) {
		printf("Enter selected cell 1-9: ");
		int scanned = scanf("%d", &move);
		if (scanned == 0) {
			printf("Invalid move! Try again.\n");
			while (getchar() != '\n');
			continue;
		}
		if (move < 1 || move > 9 ||
			board->board[(move - 1) / 3][(move - 1) % 3] != EMPTY) {
			printf("Invalid move! Try again.\n");
			continue;
		}
		return move;
	}
}