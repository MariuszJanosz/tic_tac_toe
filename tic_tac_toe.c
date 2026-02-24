#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "board.h"
#include "players.h"
#include "human_player.h"
#include "ai_player.h"
#include "menu.h"

void init_game(Board_t* board, Player_t* players) {
	srand(time(NULL));
	init_board(board);
	Option_t option = start_menu();
	switch (option) {
	case QUIT:
		exit(0);
		break;
	case TWO_PLAYERS:
		init_player(&players[0], "Player 1", human_get_move);
		init_player(&players[1], "Player 2", human_get_move);
		break;
	case PLAYER_VS_AI:
		init_player(&players[0], "Player 1", human_get_move);
		{
			option = select_ai_difficulty();
			switch (option) {
			case PLAYER_VS_AI_PERFECT:
				init_player(&players[1], "Player 2", perfect_ai_get_move);
				break;
			case PLAYER_VS_AI_HARD:
				init_player(&players[1], "Player 2", hard_ai_get_move);
				break;
			case PLAYER_VS_AI_STUPID:
				init_player(&players[1], "Player 2", stupid_ai_get_move);
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
	int rnd = 9;
	while (rnd) {
		printf("Turn of %s\n", players[player].name);
		int move = players[player].get_move(&board);
		board.board[(move - 1) / 3][(move - 1) % 3] = player == 0 ? X_ : O_;
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
