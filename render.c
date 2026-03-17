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
    if (game->side == X_) {
        gui_draw_string("Xs move!", 350, 120, 1);
    }
    else {
        gui_draw_string("Os move!", 350, 120, 1);
    }
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
    gui_draw_board(&game->board);
}

void game_over_menu_render(Game_t* game) {
    switch (game->winner) {
    case EMPTY:
        gui_draw_string("It was a tie!", 244, 380, 2);
        break;
    case X_:
        gui_draw_string("X won!", 328, 380, 2);
        break;
    case O_:
        gui_draw_string("O won!", 328, 380, 2);
        break;
    }
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