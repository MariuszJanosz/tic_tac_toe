#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "menu.h"
#include "input.h"

Option_t start_menu() {
	const char *msg =	"1. Two players\n"
						"2. Vs AI\n"
						"3. Quit\n"
						"Select game mode: ";
	const char *invalid_input_msg = "Invalid option! Try again.\n";
	while(1) {
		int opt = get_num(msg, invalid_input_msg);
		if (opt < 1 || opt > 3) {
			printf("%s", invalid_input_msg);
			continue;
		}
		switch (opt) {
		case 1:
			return TWO_PLAYERS;
		case 2:
			return PLAYER_VS_AI;
		case 3:
			return QUIT;
		}
	}
	assert(0);
}

Option_t select_ai_difficulty() {
	const char *msg =	"1. Easy\n"
						"2. Hard\n"
						"3. Perfect\n"
						"Select AI difficulty: ";
	const char *invalid_input_msg = "Invalid option! Try again.\n";
	while (1) {
		int opt = get_num(msg, invalid_input_msg);
		if (opt < 1 || opt > 3) {
			printf("%s", invalid_input_msg);
			continue;
		}
		switch (opt) {
		case 1:
			return PLAYER_VS_AI_STUPID;
		case 2:
			return PLAYER_VS_AI_HARD;
		case 3:
			return PLAYER_VS_AI_PERFECT;
		}
	}
	assert(0);
}
