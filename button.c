#include <string.h>
#include <assert.h>

#include "GLFW/glfw3.h"
#include "button.h"
#include "input.h"
#include "gui_draw.h"
#include "font_atlas.h"

void init_button(	Button_t* button, Button_id_t button_id,
					double xpos, double ypos,
					double width, double height,
					const char* desc) {
	assert(strlen(desc) < 16 && "Button desc to long!");
	button->button_id = button_id;
	button->xpos = xpos;
	button->ypos = ypos;
	button->width = width;
	button->height = height;
	button->is_pressed = 0;
	strcpy(button->desc, desc);
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
	unsigned int size = 1;
	gui_draw_string(button->desc, xpos + w + 10, ypos + (h - size * ATLAS_HEIGHT) / 2, size);
}

int mouse_is_over_button(Button_t* button, Mouse_t* mouse) {
	if (	button->xpos <= mouse->xpos && mouse->xpos <= button->xpos + button->width &&
			button->ypos <= mouse->ypos && mouse->ypos <= button->ypos + button->height) {
		return 1;
	}
	return 0;
}
