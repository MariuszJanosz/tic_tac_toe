#include <stdlib.h>
#include <stdio.h>

#include "GLFW/glfw3.h"
#include "gui_tictactoe.h"
#include "input.h"
#include "board.h"
#include "players.h"

typedef struct Game_t {
    Board_t board;
    Cell_state_t side;
    Player_t players[2];
    int vs_ai;
    Phase_t* phase;
} Game_t;

void glfw_window_init(GLFWwindow** window, int width, int height, const char* name) {
    if (!glfwInit()) {
        fprintf(stderr, "GLFW initialization failed!");
        exit(1);
    }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!*window)
    {
        glfwTerminate();
        fprintf(stderr, "GLFW window creation failed!");
        exit(1);
    }
	glfwSetMouseButtonCallback(*window, mouse_button_callback);
    glfwSetKeyCallback(*window, key_callback);
    glfwMakeContextCurrent(*window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);

	glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
}

void init_game(Game_t* game) {
    init_board(&game->board);
    game->side = X_;
    game->vs_ai = 0;
    game->phase = &phases[START_MENU];
}

int gui_main(int atgc, char** argv) {
    GLFWwindow* window = NULL;
    glfw_window_init(&window, 800, 800, "TicTacToe");

    init_phases();
    Game_t game;
    init_game(&game);

    init_mouse_input_queue();

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwWaitEvents();
    }

    glfwTerminate();
    return 0;
}