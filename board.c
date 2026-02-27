#include <stdio.h>
#include <assert.h>

#include "board.h"

char cell_state_to_char(Cell_state_t state) {
	switch (state) {
	case EMPTY:
		return ' ';
	case O_:
		return 'O';
	case X_:
		return 'X';
	}
	assert(0);
	return 0;
}

void draw_board(Board_t* board) {
	printf("#####\n");
	for (int i = 0; i < 3; ++i) {
		printf("#%c%c%c#\n",	cell_state_to_char(board->board[i][0]),
								cell_state_to_char(board->board[i][1]),
								cell_state_to_char(board->board[i][2]));
	}
	printf("#####\n");
}

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
