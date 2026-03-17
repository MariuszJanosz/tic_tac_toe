#include "phases.h"
#include "button.h"

Phase_t __phases__[NUMBER_OF_PHASES];
Phase_t* phases = __phases__;

static Phase_t init_start_menu_phase() {
	static Button_t buttons[3];
	Phase_t res;
	res.phase_id = START_MENU;
	res.buttons = buttons;
	res.button_count = 3;
	init_button(&buttons[0], START_MENU_HUMAN_VS_AI_BUTTON, 50.0, 50.0, 100.0, 50.0, "AI");
	init_button(&buttons[1], START_MENU_HUMAN_VS_HUMAN_BUTTON, 50.0, 150.0, 100.0, 50.0, "Two players");
	init_button(&buttons[2], START_MENU_QUIT_BUTTON, 50.0, 250.0, 100.0, 50.0, "Quit");
	return res;
}

static Phase_t init_ai_side_menu_phase() {
	static Button_t buttons[2];
	Phase_t res;
	res.phase_id = AI_SIDE_MENU;
	res.buttons = buttons;
	res.button_count = 2;
	init_button(&buttons[0], AI_SIDE_X_BUTTON, 50.0, 50.0, 100.0, 50.0, "X");
	init_button(&buttons[1], AI_SIDE_O_BUTTON, 50.0, 150.0, 100.0, 50.0, "O");
	return res;
}

static Phase_t init_ai_difficulty_menu_phase() {
	static Button_t buttons[3];
	Phase_t res;
	res.phase_id = AI_DIFFICULTY_MENU;
	res.buttons = buttons;
	res.button_count = 3;
	init_button(&buttons[0], AI_DIFFICULTY_MENU_EASY_BUTTON, 50.0, 50.0, 100.0, 50.0, "Easy");
	init_button(&buttons[1], AI_DIFFICULTY_MENU_HARD_BUTTON, 50.0, 150.0, 100.0, 50.0, "Hard");
	init_button(&buttons[2], AI_DIFFICULTY_MENU_PERFECT_BUTTON, 50.0, 250.0, 100.0, 50.0, "Impossible");
	return res;
}

static Phase_t init_game_phase() {
	static Button_t buttons[9];
	Phase_t res;
	res.phase_id = GAME;
	res.buttons = buttons;
	res.button_count = 9;
	init_button(&buttons[0], GAME_CELL_1_BUTTON, 1 * 160.0, 1 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[1], GAME_CELL_2_BUTTON, 2 * 160.0, 1 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[2], GAME_CELL_3_BUTTON, 3 * 160.0, 1 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[3], GAME_CELL_4_BUTTON, 1 * 160.0, 2 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[4], GAME_CELL_5_BUTTON, 2 * 160.0, 2 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[5], GAME_CELL_6_BUTTON, 3 * 160.0, 2 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[6], GAME_CELL_7_BUTTON, 1 * 160.0, 3 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[7], GAME_CELL_8_BUTTON, 2 * 160.0, 3 * 160.0, 160.0, 160.0, "");
	init_button(&buttons[8], GAME_CELL_9_BUTTON, 3 * 160.0, 3 * 160.0, 160.0, 160.0, "");
	return res;
}

static Phase_t init_game_over_menu_phase() {
	static Button_t buttons[2];
	Phase_t res;
	res.phase_id = GAME_OVER_MENU;
	res.buttons = buttons;
	res.button_count = 2;
	init_button(&buttons[0], GAME_OVER_MENU_PLAY_AGAIN_BUTTON, 50.0, 50.0, 100.0, 50.0, "Play again");
	init_button(&buttons[1], GAME_OVER_MENU_QUIT_BUTTON, 50.0, 150.0, 100.0, 50.0, "Quit");
	return res;
}

void init_phases() {
	phases[START_MENU] = init_start_menu_phase();
	phases[AI_SIDE_MENU] = init_ai_side_menu_phase();
	phases[AI_DIFFICULTY_MENU] = init_ai_difficulty_menu_phase();
	phases[GAME] = init_game_phase();
	phases[GAME_OVER_MENU] = init_game_over_menu_phase();
}

Button_id_t get_activated_button(Phase_t* phase) {
	Button_id_t res = NONE_BUTTON;
	for (int i = 0; i < mouse_input_queue_rear; ++i) {
		if (mouse_input_queue[i].lmb_is_pressed) {
			for (int j = 0; j < phase->button_count; ++j) {
				if (mouse_is_over_button(&phase->buttons[j], &mouse_input_queue[i])) {
					phase->buttons[j].is_pressed = 1;
				}
			}
		}
		else {
			for (int j = 0; j < phase->button_count; ++j) {
				if (mouse_is_over_button(&phase->buttons[j], &mouse_input_queue[i]) &&
					phase->buttons[j].is_pressed) {
					res = phase->buttons[j].button_id;
				}
				phase->buttons[j].is_pressed = 0;
			}
		}
	}
	mouse_input_queue_rear = 0;
	return res;
}
