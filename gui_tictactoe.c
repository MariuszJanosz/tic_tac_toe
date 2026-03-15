#include <stdlib.h>
#include <stdio.h>

#include "GLFW/glfw3.h"
#include "gui_tictactoe.h"
#include "players.h"
#include "phases.h"
#include "update.h"
#include "render.h"
#include "font_atlas.h"

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

    glGenTextures(1, &font_atlas_tex);
    glBindTexture(GL_TEXTURE_2D, font_atlas_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ATLAS_WIDTH, ATLAS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &font_atlas_data->RGBA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
        render(&game);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        update(&game);
    }

    glfwTerminate();
    return 0;
}