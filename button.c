#include "GLFW/glfw3.h"
#include "button.h"

void init_button(Button_t* button, Button_id_t button_id, double xpos, double ypos, double width, double height) {
	button->button_id = button_id;
	button->xpos = xpos;
	button->ypos = ypos;
	button->width = width;
	button->height = height;
	button->is_pressed = 0;
}

void draw_button(Button_t* button) {
	GLdouble	xpos = button->xpos, ypos = button->ypos,
				w = button->width, h = button->height;
	GLubyte r = 0, g = 0, b = 0;
	glColor3ub(r, g, b);
	glBegin(GL_LINE_LOOP);

	glVertex2d(xpos, ypos);
	glVertex2d(xpos + w, ypos);
	glVertex2d(xpos + w, ypos + h);
	glVertex2d(xpos, ypos + h);
	glEnd();
}