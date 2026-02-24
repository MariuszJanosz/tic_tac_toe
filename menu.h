#ifndef MENU_H
#define MENU_H

typedef enum {
	TWO_PLAYERS,
	PLAYER_VS_AI,
	PLAYER_VS_AI_PERFECT,
	PLAYER_VS_AI_HARD,
	PLAYER_VS_AI_STUPID,
	PLAY_AGAIN,
	QUIT
} Option_t;

Option_t start_menu();
Option_t select_ai_difficulty();
Option_t play_again();

#endif //MENU_H