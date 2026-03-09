#ifndef BUTTON_H
#define BUTTON_H

typedef struct Button_t {
	double xpos;
	double ypos;
	double width;
	double height;
	int is_pressed;
} Button_t;

void init_button(Button_t* button, double xpos, double ypos, double width, double height);
void draw_button(Button_t* button);

#endif //BUTTON_H