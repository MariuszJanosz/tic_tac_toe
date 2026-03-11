#ifndef BUTTON_H
#define BUTTON_H

#include "input.h"

typedef enum {
	NONE_BUTTON,
	START_MENU_HUMAN_VS_AI_BUTTON,
	START_MENU_HUMAN_VS_HUMAN_BUTTON,
	START_MENU_QUIT_BUTTON,
	AI_DIFFICULTY_MENU_EASY_BUTTON,
	AI_DIFFICULTY_MENU_HARD_BUTTON,
	AI_DIFFICULTY_MENU_PERFECT_BUTTON,
	GAME_CELL_1_BUTTON,
	GAME_CELL_2_BUTTON,
	GAME_CELL_3_BUTTON,
	GAME_CELL_4_BUTTON,
	GAME_CELL_5_BUTTON,
	GAME_CELL_6_BUTTON,
	GAME_CELL_7_BUTTON,
	GAME_CELL_8_BUTTON,
	GAME_CELL_9_BUTTON,
	GAME_OVER_MENU_PLAY_AGAIN_BUTTON,
	GAME_OVER_MENU_QUIT_BUTTON
} Button_id_t;

typedef struct Button_t {
	Button_id_t button_id;
	double xpos;
	double ypos;
	double width;
	double height;
	int is_pressed;
} Button_t;

void init_button(Button_t* button, Button_id_t button_id, double xpos, double ypos, double width, double height);
void draw_button(Button_t* button);
int mouse_is_over_button(Button_t* button, Mouse_t* mouse);

#endif //BUTTON_H