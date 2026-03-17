#include "update.h"
#include "gui_tictactoe.h"
#include "input.h"
#include "board.h"
#include "phases.h"
#include "players.h"
#include "button.h"
#include "human_player.h"
#include "ai_player.h"
#include "GLFW/glfw3.h"
#include "phases.h"

void start_menu_update(Game_t* game) {
    Button_id_t button_id = get_activated_button(game->phase);
    switch (button_id) {
    case START_MENU_HUMAN_VS_AI_BUTTON:
        init_player(&game->players[0], "Player 1", NULL);
        game->phase = &phases[AI_DIFFICULTY_MENU];
        game->vs_ai = 1;
        break;
    case START_MENU_HUMAN_VS_HUMAN_BUTTON:
        init_player(&game->players[0], "Player 1", NULL);
        init_player(&game->players[1], "Player 2", NULL);
        game->phase = &phases[GAME];
        game->vs_ai = 0;
        break;
    case START_MENU_QUIT_BUTTON:
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
        break;
    default:
        break;
    }
}

void ai_difficulty_menu_update(Game_t* game) {
    Button_id_t button_id = get_activated_button(game->phase);
    switch (button_id) {
    case AI_DIFFICULTY_MENU_EASY_BUTTON:
        init_player(&game->players[1], "Stupid AI", stupid_ai_get_move);
        game->phase = &phases[GAME];
        break;
    case AI_DIFFICULTY_MENU_HARD_BUTTON:
        init_player(&game->players[1], "Hard AI", hard_ai_get_move);
        game->phase = &phases[GAME];
        break;
    case AI_DIFFICULTY_MENU_PERFECT_BUTTON:
        init_player(&game->players[1], "Perfect AI", perfect_ai_get_move);
        game->phase = &phases[GAME];
        break;
    default:
        break;
    }
}

void game_update(Game_t* game) {
    Button_id_t button_id = get_activated_button(game->phase);
    int move = 0;
    switch (button_id) {
    case GAME_CELL_1_BUTTON:
        move = 1;
        break;
    case GAME_CELL_2_BUTTON:
        move = 2;
        break;
    case GAME_CELL_3_BUTTON:
        move = 3;
        break;
    case GAME_CELL_4_BUTTON:
        move = 4;
        break;
    case GAME_CELL_5_BUTTON:
        move = 5;
        break;
    case GAME_CELL_6_BUTTON:
        move = 6;
        break;
    case GAME_CELL_7_BUTTON:
        move = 7;
        break;
    case GAME_CELL_8_BUTTON:
        move = 8;
        break;
    case GAME_CELL_9_BUTTON:
        move = 9;
        break;
    default:
        break;
    }
    if (full_board(&game->board)) {
        game->phase = &phases[GAME_OVER_MENU];
        game->winner = EMPTY;
        return;
    }
    if (!valid_move(&game->board, move)) {
        return;
    }
    apply_move(&game->board, move, game->side);
    if (solved(&game->board)) {
        game->phase = &phases[GAME_OVER_MENU];
        game->winner = game->side;
        return;
    }
    else if (full_board(&game->board)) {
        game->phase = &phases[GAME_OVER_MENU];
        game->winner = EMPTY;
        return;
    }
    game->side = game->side == X_ ? O_ : X_;
    if (game->vs_ai) {
        move = game->players[1].get_move(&game->board);
        apply_move(&game->board, move, game->side);
        if (solved(&game->board)) {
            game->phase = &phases[GAME_OVER_MENU];
            game->winner = game->side;
            return;
        }
        game->side = game->side == X_ ? O_ : X_;
    }
}

void game_over_menu_update(Game_t* game) {
    Button_id_t button_id = get_activated_button(game->phase);
    switch (button_id) {
    case GAME_OVER_MENU_PLAY_AGAIN_BUTTON:
        init_game(game);
        break;
    case GAME_OVER_MENU_QUIT_BUTTON:
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
        break;
    default:
        break;
    }
}

void update(Game_t* game) {
    switch (game->phase->phase_id) {
    case START_MENU:
        start_menu_update(game);
        break;
    case AI_DIFFICULTY_MENU:
        ai_difficulty_menu_update(game);
        break;
    case GAME:
        game_update(game);
        break;
    case GAME_OVER_MENU:
        game_over_menu_update(game);
        break;
    }
}
