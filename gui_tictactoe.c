#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#endif

#include "GLFW/glfw3.h"
#include "gui_tictactoe.h"
#include "players.h"
#include "phases.h"
#include "update.h"
#include "render.h"
#include "font_atlas.h"

unsigned long long get_time_ms() {
    unsigned long long res = 0;
#ifdef _WIN32
    res = GetTickCount64();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    res = (unsigned long long)(ts.tv_sec) * 1000 +
        (unsigned long long)(ts.tv_nsec) / 1000000;
#endif
    return res;
}

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
    game->winner = EMPTY;
    game->vs_ai = 0;
    game->ai_side = O_;
    game->phase = &phases[START_MENU];
    game->dt = 0;
    game->is_over = 0;
}

int gui_main(int atgc, char** argv) {
    GLFWwindow* window = NULL;
    glfw_window_init(&window, 800, 800, "TicTacToe");

    init_phases();
    Game_t game;
    init_game(&game);

    init_mouse_input_queue();

    unsigned long long prev_time = get_time_ms();
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
        render(&game);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        unsigned long long curr_time = get_time_ms();
        game.dt = curr_time - prev_time;
        prev_time = curr_time;
        update(&game);
    }

    glfwTerminate();
    return 0;
}