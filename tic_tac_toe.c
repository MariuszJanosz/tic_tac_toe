#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "players.h"
#include "human_player.h"
#include "ai_player.h"
#include "menu.h"
#include "input.h"

void init_game(Board_t* board, Player_t* players) {
	srand((unsigned int)time(NULL));
	init_board(board);
	Option_t option = start_menu();
	switch (option) {
	case QUIT:
		exit(0);
		break;
	case TWO_PLAYERS:
	{
		printf("Player 1\n");
		char* name = get_player_name();
		init_player(&players[0], name, human_get_move);
		free(name);
		printf("Player 2\n");
		name = get_player_name();
		init_player(&players[1], name, human_get_move);
		free(name);
		break;
	}
	case PLAYER_VS_AI:
	{
		printf("Player 1\n");
		char* name = get_player_name();;
		init_player(&players[0], name, human_get_move);
		free(name);
	}
		{
			option = select_ai_difficulty();
			switch (option) {
			case PLAYER_VS_AI_PERFECT:
				init_player(&players[1], "perfect AI", perfect_ai_get_move);
				break;
			case PLAYER_VS_AI_HARD:
				init_player(&players[1], "hard AI", hard_ai_get_move);
				break;
			case PLAYER_VS_AI_STUPID:
				init_player(&players[1], "easy AI", stupid_ai_get_move);
				break;
			}
		}
		break;
	}
}

int main(int argc, char** argv) {
	Board_t board;
	Player_t players[2];
start:
	init_game(&board, players);
	
	int player = 0;
	Cell_state_t player_to_side[2] = {X_, O_};
	int rnd = 9;
	while (rnd) {
		printf("Turn of %s\n", players[player].name);
		int move = players[player].get_move(&board);
		apply_move(&board, move, player_to_side[player]);
		draw_board(&board);
		if (solved(&board)) {
			break;
		}
		player ^= 1;
		--rnd;
	}
	if (rnd) {
		printf("%s won!\n", players[player].name);
	}
	else {
		printf("It's a tie!\n");
	}
	Option_t option = play_again();
	if (option == PLAY_AGAIN) {
		goto start;
	}
	return 0;
}
