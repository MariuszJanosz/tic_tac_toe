#ifndef GUI_TICTACTOE_H
#define GUI_TICTACTOE_H

#include "board.h"
#include "players.h"
#include "phases.h"

typedef struct Game_t {
    Board_t board;
    Cell_state_t side;
    Player_t players[2];
    int vs_ai;
    Phase_t* phase;
} Game_t;

int gui_main(int atgc, char** argv);
void init_game(Game_t* game);

#endif //GUI_TICTACTOE_H