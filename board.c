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