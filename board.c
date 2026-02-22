#include <stdio.h>

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
}

void draw_board(Board_t* board) {
	for (int i = 0; i < 3; ++i) {
		printf("%c %c %c\n\n",	cell_state_to_char(board->board[i][0]),
								cell_state_to_char(board->board[i][1]),
								cell_state_to_char(board->board[i][2]));
	}
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