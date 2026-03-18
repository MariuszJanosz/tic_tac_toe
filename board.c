#include <stdio.h>
#include <assert.h>

#include "board.h"

void init_board(Board_t* board) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			board->board[i][j] = EMPTY;
		}
	}
}

int solved(Board_t* board) {
	if (board->board[0][0] != EMPTY && board->board[0][0] == board->board[0][1] && board->board[0][0] == board->board[0][2]) {
		return 1; //1st row
	}
	if (board->board[1][0] != EMPTY && board->board[1][0] == board->board[1][1] && board->board[1][0] == board->board[1][2]) {
		return 1; //2nd row
	}
	if (board->board[2][0] != EMPTY && board->board[2][0] == board->board[2][1] && board->board[2][0] == board->board[2][2]) {
		return 1; //3rd row
	}
	if (board->board[0][0] != EMPTY && board->board[0][0] == board->board[1][0] && board->board[0][0] == board->board[2][0]) {
		return 1; //1st col
	}
	if (board->board[0][1] != EMPTY && board->board[0][1] == board->board[1][1] && board->board[0][1] == board->board[2][1]) {
		return 1; //2nd col
	}
	if (board->board[0][2] != EMPTY && board->board[0][2] == board->board[1][2] && board->board[0][2] == board->board[2][2]) {
		return 1; //3rd col
	}
	if (board->board[0][0] != EMPTY && board->board[0][0] == board->board[1][1] && board->board[0][0] == board->board[2][2]) {
		return 1; //main diag
	}
	if (board->board[2][0] != EMPTY && board->board[2][0] == board->board[1][1] && board->board[2][0] == board->board[0][2]) {
		return 1; //anti diag
	}
	return 0; //no winning line
}

void apply_move(Board_t* board, int move, Cell_state_t side) {
	assert(1 <= move && move <= 9 && board->board[(move - 1) / 3][(move - 1) % 3] == EMPTY && "Invalid move!");
	board->board[(move - 1) / 3][(move - 1) % 3] = side;
}

int valid_move(Board_t* board, int move) {
	return 1 <= move && move <= 9 && board->board[(move - 1) / 3][(move - 1) % 3] == EMPTY;
}

int full_board(Board_t* board) {
	return	(board->board[0][0] != EMPTY) && (board->board[0][1] != EMPTY) && (board->board[0][2] != EMPTY) &&
			(board->board[1][0] != EMPTY) && (board->board[1][1] != EMPTY) && (board->board[1][2] != EMPTY) &&
			(board->board[2][0] != EMPTY) && (board->board[2][1] != EMPTY) && (board->board[2][2] != EMPTY);
}

void detect_winning_lines(Board_t* board, int* out_array, int* out_count) {
	*out_count = 0;
	if (board->board[0][0] != EMPTY && board->board[0][0] == board->board[0][1] && board->board[0][0] == board->board[0][2]) {
		out_array[*out_count] = FIRST_ROW;
		*out_count += 1;
	}
	if (board->board[1][0] != EMPTY && board->board[1][0] == board->board[1][1] && board->board[1][0] == board->board[1][2]) {
		out_array[*out_count] = SECOND_ROW;
		*out_count += 1;
	}
	if (board->board[2][0] != EMPTY && board->board[2][0] == board->board[2][1] && board->board[2][0] == board->board[2][2]) {
		out_array[*out_count] = THITD_ROW;
		*out_count += 1;
	}
	if (board->board[0][0] != EMPTY && board->board[0][0] == board->board[1][0] && board->board[0][0] == board->board[2][0]) {
		out_array[*out_count] = FIRST_COLUMN;
		*out_count += 1;
	}
	if (board->board[0][1] != EMPTY && board->board[0][1] == board->board[1][1] && board->board[0][1] == board->board[2][1]) {
		out_array[*out_count] = SECOND_COLUMN;
		*out_count += 1;
	}
	if (board->board[0][2] != EMPTY && board->board[0][2] == board->board[1][2] && board->board[0][2] == board->board[2][2]) {
		out_array[*out_count] = THIRD_COLUMN;
		*out_count += 1;
	}
	if (board->board[0][0] != EMPTY && board->board[0][0] == board->board[1][1] && board->board[0][0] == board->board[2][2]) {
		out_array[*out_count] = MAIN_DIAGONAL;
		*out_count += 1;
	}
	if (board->board[2][0] != EMPTY && board->board[2][0] == board->board[1][1] && board->board[2][0] == board->board[0][2]) {
		out_array[*out_count] = COUNTERDIAGONAL;
		*out_count += 1;
	}
}
