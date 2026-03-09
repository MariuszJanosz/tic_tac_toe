#ifndef INPUT_H
#define INPUT_H

#include "GLFW/glfw3.h"

typedef struct Mouse_t {
	double xpos;
	double ypos;
	int lmb_is_pressed;
} Mouse_t;

extern Mouse_t mouse;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int get_num(const char* msg, const char* invalid_input_msg);
char* get_string(const char* msg, const char* invalid_input_msg);
char* terminal_get_player_name();

#endif //INPUT_H