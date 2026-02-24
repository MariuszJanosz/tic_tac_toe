#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "menu.h"

void print_start_screen();
void print_ai_difficulty_selection_screen();

Option_t start_menu() {
	do {
		print_start_screen();
		int opt;
		int scanned = scanf("%d", &opt);
		if (scanned == 0) {
			char ch;
			while ((ch = getchar()) != '\n');
			printf("Invalid option! Try again.\n");
			continue;
		}
		if (opt < 1 || opt > 3) {
			char ch;
			while ((ch = getchar()) != '\n');
			printf("Invalid option! Try again.\n");
			continue;
		}
		while (getchar() != '\n');
		switch (opt) {
		case 1:
			return TWO_PLAYERS;
		case 2:
			return PLAYER_VS_AI;
		case 3:
			return QUIT;
		}
	} while (1);
	assert(0);
}

Option_t select_ai_difficulty() {
	do {
		print_ai_difficulty_selection_screen();
		int opt;
		int scanned = scanf("%d", &opt);
		if (scanned == 0) {
			char ch;
			while ((ch = getchar()) != '\n');
			printf("Invalid option! Try again.\n");
			continue;
		}
		if (opt < 1 || opt > 3) {
			char ch;
			while ((ch = getchar()) != '\n');
			printf("Invalid option! Try again.\n");
			continue;
		}
		while (getchar() != '\n');
		switch (opt) {
		case 1:
			return PLAYER_VS_AI_STUPID;
		case 2:
			return PLAYER_VS_AI_HARD;
		case 3:
			return PLAYER_VS_AI_PERFECT;
		}
	} while (1);
	assert(0);
}

void print_start_screen() {
	printf("1. Two players\n");
	printf("2. Vs AI\n");
	printf("3. Quit\n");
	printf("Select game mode: ");
}

void print_ai_difficulty_selection_screen() {
	printf("1. Easy\n");
	printf("2. Hard\n");
	printf("3. Perfect\n");
	printf("Select AI difficulty: ");
}