#include <stdio.h>
#include <stdlib.h>

#include "ai_player.h"
#include "board.h"

static int ai_get_move(Board_t* board) {
	//old_is_top_lvl is 1 if it is a top level of recursion, 0 otherwise
	static int is_top_lvl = 1;
	int old_is_top_lvl = is_top_lvl;
	is_top_lvl = 0;
	//List remaining empty cells.
	int possible_moves[9];
	int possible_moves_count = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board->board[i][j] == EMPTY) {
				possible_moves[possible_moves_count++] = 3 * i + j + 1;
			}
		}
	}

	//If there are no moves left, it is a tie
	if (possible_moves_count == 0) {
		is_top_lvl = old_is_top_lvl;
		return 0;
	}

	//Determine which player is currently playing.
	Cell_state_t curr_player = possible_moves_count % 2 == 1 ? X_ : O_;

	int best_move = 0;
	int best_score = -2;
	for (int i = 0; i < possible_moves_count; ++i) {
		int move = possible_moves[i];
		board->board[(move - 1) / 3][(move - 1) % 3] = curr_player;
		//If current player has a winning move no need to recurse deeper
		if (solved(board)) {
			board->board[(move - 1) / 3][(move - 1) % 3] = EMPTY;
			is_top_lvl = old_is_top_lvl;
			if (old_is_top_lvl) {
				return move;
			}
			return 1;
		}
		int score = -ai_get_move(board);
		if (score > best_score) {
			best_score = score;
			best_move = move;
		}
		board->board[(move - 1) / 3][(move - 1) % 3] = EMPTY;
	}
	is_top_lvl = old_is_top_lvl;
	if (old_is_top_lvl) {
		return best_move;
	}
	return best_score;
}

int perfect_ai_get_move(Board_t* board) {
	return ai_get_move(board);
}

int stupid_ai_get_move(Board_t* board) {
	int possible_moves[9];
	int possible_moves_count = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board->board[i][j] == EMPTY) {
				possible_moves[possible_moves_count++] = 3 * i + j + 1;
			}
		}
	}
	int rnd = rand() % possible_moves_count;
	return possible_moves[rnd];
}

int hard_ai_get_move(Board_t* board) {
	int perfect_move = ai_get_move(board);
	int rnd = rand() % 10;
	if (rnd < 9) {
		return perfect_move;
	}
	else {
		return stupid_ai_get_move(board);
	}
}