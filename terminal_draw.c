#include <stdio.h>
#include <assert.h>

#include "terminal_draw.h"

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

void terminal_draw_board(Board_t* board) {
	printf("#####\n");
	for (int i = 0; i < 3; ++i) {
		printf("#%c%c%c#\n", cell_state_to_char(board->board[i][0]),
			cell_state_to_char(board->board[i][1]),
			cell_state_to_char(board->board[i][2]));
	}
	printf("#####\n");
}