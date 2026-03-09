#include <stdlib.h>
#include <stdio.h>

#include "GLFW/glfw3.h"
#include "gui_tictactoe.h"
#include "input.h"

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
    glfwMakeContextCurrent(*window);

	glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
}

int gui_main(int atgc, char** argv) {
    GLFWwindow* window = NULL;
    glfw_window_init(&window, 800, 800, "TicTacToe");

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