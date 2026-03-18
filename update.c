#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#endif

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
        init_player(&game->players[1], "Player 2", NULL);
        game->phase = &phases[AI_SIDE_MENU];
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

void ai_side_menu_update(Game_t* game) {
    Button_id_t button_id = get_activated_button(game->phase);
    switch (button_id) {
    case AI_SIDE_X_BUTTON:
        game->ai_side = X_;
        game->phase = &phases[AI_DIFFICULTY_MENU];
        break;
    case AI_SIDE_O_BUTTON:
        game->ai_side = O_;
        game->phase = &phases[AI_DIFFICULTY_MENU];
        break;
    default:
        break;
    }
}

void ai_difficulty_menu_update(Game_t* game) {
    Button_id_t button_id = get_activated_button(game->phase);
    int player_num = game->ai_side == X_ ? 0 : 1;
    switch (button_id) {
    case AI_DIFFICULTY_MENU_EASY_BUTTON:
        init_player(&game->players[player_num], "Stupid AI", stupid_ai_get_move);
        game->phase = &phases[GAME];
        break;
    case AI_DIFFICULTY_MENU_HARD_BUTTON:
        init_player(&game->players[player_num], "Hard AI", hard_ai_get_move);
        game->phase = &phases[GAME];
        break;
    case AI_DIFFICULTY_MENU_PERFECT_BUTTON:
        init_player(&game->players[player_num], "Perfect AI", perfect_ai_get_move);
        game->phase = &phases[GAME];
        break;
    default:
        break;
    }
}

void game_update(Game_t* game) {
#define AI_PAUSE_TIME_MS 350
    //If game is over switch to GAME_OVER_MENU phase on next lmb press
    if (game->is_over) {
        if (mouse_input_queue_rear) {
            for (int i = 0; i < mouse_input_queue_rear; ++i) {
                if (mouse_input_queue[i].lmb_is_pressed) {
                    game->phase = &phases[GAME_OVER_MENU];
                    mouse_input_queue_rear;
                    return;
                }
            }
        }
        return;
    }
    //Make sure mouse input queue is emptied
    Button_id_t button_id = get_activated_button(game->phase);
    int move = 0;
    if (game->vs_ai && game->side == game->ai_side) { //AI move
        int player_num = game->side == X_ ? 0 : 1;
        move = game->players[player_num].get_move(&game->board);
        //Wait some time to make it appear as AI need some time to make a decision
        unsigned int time = AI_PAUSE_TIME_MS;
#ifdef _WIN32
        Sleep(time);
#else
        const struct timespec duration = { 0, time * 1000000 };
        nanosleep(&duration, NULL);
#endif
    }
    else { //Human move
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
        //Invalid move nothing happens, try again in next frame
        if (!valid_move(&game->board, move)) {
            return;
        }
    }
    apply_move(&game->board, move, game->side);
    game->phase->animations[move - 1].is_animating = 1;
    game->phase->animations[move - 1].time = 1000;
    if (game->side == game->ai_side) {
        game->phase->animations[move - 1].time += AI_PAUSE_TIME_MS;
    }
    game->phase->animations[move - 1].time_elapsed = 0;
    //Chcek for winner
    if (solved(&game->board)) {
        game->is_over = 1;
        game->winner = game->side;
        return;
    }
    //If no winner but full board it's a tie
    else if (full_board(&game->board)) {
        game->is_over = 1;
        game->winner = EMPTY;
        return;
    }
    //Switch side
    game->side = game->side == X_ ? O_ : X_;
#undef AI_PAUSE_TIME_MS
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
    case AI_SIDE_MENU:
        ai_side_menu_update(game);
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
