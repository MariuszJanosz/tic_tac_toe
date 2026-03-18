#include <string.h>

#include "render.h"
#include "gui_tictactoe.h"
#include "GLFW/glfw3.h"
#include "button.h"
#include "phases.h"
#include "gui_draw.h"
#include "board.h"

void start_menu_render(Game_t* game) {
    gui_draw_string("Select game mode:", 160, 20, 1);
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
}

void ai_side_menu_render(Game_t* game) {
    gui_draw_string("Select AI side:", 160, 20, 1);
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
}

void ai_difficulty_menu_render(Game_t* game) {
    gui_draw_string("Select AI difficulty:", 160, 20, 1);
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
}

void game_render(Game_t* game) {
    if (!game->is_over) {
        if (game->side == X_) {
            gui_draw_string("Xs move!", (double)(800 - strlen("Xs move!") * 12) / 2, 120, 1);
        }
        else {
            gui_draw_string("Os move!", (double)(800 - strlen("Os move!") * 12) / 2, 120, 1);
        }
    }
    else {
        gui_draw_string("GAME OVER! Press LMB to continue.",
                        (double)(800 - strlen("GAME OVER! Press LMB to continue.") * 12) / 2, 120, 1);
    }
    gui_draw_board(game);
    if (game->is_over) {
        switch (game->winner) {
        case EMPTY:
            gui_draw_string("It is a tie!", (double)(800 - strlen("It is a tie!") * 12 * 2) / 2, 380, 2);
            break;
        case X_:
            gui_draw_string("X wins!", (double)(800 - strlen("X wins!") * 12 * 2) / 2, 380, 2);
            break;
        case O_:
            gui_draw_string("O wins!", (double)(800 - strlen("X wins!") * 12 * 2) / 2, 380, 2);
            break;
        }
    }
}

void game_over_menu_render(Game_t* game) {
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
}

void render(Game_t* game) {
    switch (game->phase->phase_id) {
    case START_MENU:
        start_menu_render(game);
        break;
    case AI_SIDE_MENU:
        ai_side_menu_render(game);
        break;
    case AI_DIFFICULTY_MENU:
        ai_difficulty_menu_render(game);
        break;
    case GAME:
        game_render(game);
        break;
    case GAME_OVER_MENU:
        game_over_menu_render(game);
        break;
    }
}