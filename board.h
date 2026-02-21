#ifndef BOARD_H
#define BOARD_H

typedef enum Cell_state_t {
	EMPTY,
	O_,
	X_
} Cell_state_t;

typedef struct Board_t {
	Cell_state_t board[3][3];
} Board_t;

void draw_board(Board_t* board);

#endif //BOARD_H