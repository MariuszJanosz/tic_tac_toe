#include <stdio.h>
#include <assert.h>

#include "human_player.h"
#include "board.h"
#include "input.h"

int human_get_move(Board_t* board) {
	const char *msg = "Enter selected cell 1-9: ";
	const char *invalid_input_msg = "Invalid move! Try again.\n";
	while (1) {
		int move = get_num(msg, invalid_input_msg);
		if (move < 1 || move > 9 ||
			board->board[(move - 1) / 3][(move - 1) % 3] != EMPTY) {
			printf("%s", invalid_input_msg);
			continue;
		}
		return move;
	}
	assert(0);
}