#ifndef GUI_DRAW_H
#define GUI_DRAW_H

#include "board.h"

void gui_draw_board(Board_t* board);
void gui_draw_string(const char* str, double xpos, double ypos, unsigned int size);

#endif //GUI_DRAW_H
