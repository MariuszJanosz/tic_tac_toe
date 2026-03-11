#ifndef INPUT_H
#define INPUT_H

#include "GLFW/glfw3.h"

#define MOUSE_INPUT_QUEUE_SIZE 64

typedef struct Mouse_t {
	double xpos;
	double ypos;
	int lmb_is_pressed;
} Mouse_t;

extern Mouse_t* mouse_input_queue;
extern int mouse_input_queue_rear;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void init_mouse_input_queue();
void free_mouse_input_queue(void);

int get_num(const char* msg, const char* invalid_input_msg);
char* get_string(const char* msg, const char* invalid_input_msg);
char* terminal_get_player_name();

#endif //INPUT_H