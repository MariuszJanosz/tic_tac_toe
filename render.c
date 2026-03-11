#include "render.h"
#include "gui_tictactoe.h"
#include "GLFW/glfw3.h"
#include "button.h"
#include "phases.h"
#include "gui_draw.h"

void start_menu_render(Game_t* game) {
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
}

void ai_difficulty_menu_render(Game_t* game) {
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
}

void game_render(Game_t* game) {
    for (int i = 0; i < game->phase->button_count; ++i) {
        draw_button(&game->phase->buttons[i]);
    }
    gui_draw_board(&game->board);
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