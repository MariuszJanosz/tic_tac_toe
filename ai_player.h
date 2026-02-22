#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "board.h"

int perfect_ai_get_move(Board_t* board);
int hard_ai_get_move(Board_t* board);
int stupid_ai_get_move(Board_t* board);

#endif //AI_PLAYER_H