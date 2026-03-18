#ifndef BOARD_H
#define BOARD_H

typedef enum Cell_state_t {
	EMPTY,
	O_,
	X_
} Cell_state_t;

typedef enum Board_line_t {
	FIRST_ROW,
	SECOND_ROW,
	THITD_ROW,
	FIRST_COLUMN,
	SECOND_COLUMN,
	THIRD_COLUMN,
	MAIN_DIAGONAL,
	COUNTERDIAGONAL
} Board_line_t;

typedef struct Board_t {
	Cell_state_t board[3][3];
} Board_t;

void init_board(Board_t* board);
int solved(Board_t* board);
void apply_move(Board_t* board, int move, Cell_state_t side);
int valid_move(Board_t* board, int move);
int full_board(Board_t* board);
void detect_winning_lines(Board_t* board, int* out_array, int* out_count);

#endif //BOARD_H