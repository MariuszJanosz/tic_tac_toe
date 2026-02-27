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

void init_board(Board_t* board);
void draw_board(Board_t* board);
int solved(Board_t* board);
void apply_move(Board_t* board, int move, Cell_state_t side);

#endif //BOARD_H