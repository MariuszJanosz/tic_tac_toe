#include "GLFW/glfw3.h"
#include "gui_draw.h"
#include "board.h"
#include "math.h"
#include "font_atlas.h"

void gui_draw_board(Game_t* game) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			GLdouble xmid = 240.0 + j * 160.0;
			GLdouble ymid = 240.0 + i * 160.0;
			GLdouble cell_w = 160.0, cell_h = 160.0;
			glColor3ub(0, 0, 0);
			//Draw cell boundary
			glBegin(GL_LINE_LOOP);
			glVertex2d(xmid - cell_w / 2, ymid - cell_h / 2);
			glVertex2d(xmid - cell_w / 2, ymid + cell_h / 2);
			glVertex2d(xmid + cell_w / 2, ymid + cell_h / 2);
			glVertex2d(xmid + cell_w / 2, ymid - cell_h / 2);
			glEnd();
			//If cell is occupied draw appropriate letter
			if (game->board.board[i][j] == X_) {
				GLdouble arm_len = 40.0;
				glBegin(GL_LINE_LOOP);
				glVertex2d(xmid, ymid);
				glVertex2d(xmid - arm_len, ymid + arm_len);
				glVertex2d(xmid, ymid);
				glVertex2d(xmid + arm_len, ymid + arm_len);
				glVertex2d(xmid, ymid);
				glVertex2d(xmid + arm_len, ymid - arm_len);
				glVertex2d(xmid, ymid);
				glVertex2d(xmid - arm_len, ymid - arm_len);
				glVertex2d(xmid, ymid);
				glEnd();
			}
			else if (game->board.board[i][j] == O_) {
				GLdouble R = 40.0;
				glBegin(GL_LINE_LOOP);
#define CIRCEL_STEPS 32
				for (int i = 0; i < CIRCEL_STEPS; ++i) {
					GLdouble x = xmid + R * cos(2 * 3.141592 * i / CIRCEL_STEPS);
					GLdouble y = ymid + R * sin(2 * 3.141592 * i / CIRCEL_STEPS);
					glVertex2d(x, y);
				}
#undef CIRCLE_STEPS
				glEnd();
			}
		}
	}
}

void gui_draw_string(const char* str, double xpos, double ypos, unsigned int size) {
	int i = 0;
	double width = 12.0 * size;
	double height = width * 20 / 12;
	glEnable(GL_TEXTURE_2D);
	while (str[i]) {
		glBegin(GL_QUADS);
		glTexCoord2d((12.0 * str[i]) / font_atlas_data->width, 0.0);
		glVertex2d(xpos + width * i, ypos);
		glTexCoord2d((12.0 * str[i] + 12.0) / font_atlas_data->width, 0.0);
		glVertex2d(xpos + width * i + width, ypos);
		glTexCoord2d((12.0 * str[i] + 12.0) / font_atlas_data->width, 0.0 + 1.0);
		glVertex2d(xpos + width * i + width, ypos + height);
		glTexCoord2d((12.0 * str[i]) / font_atlas_data->width, 0.0 + 1.0);
		glVertex2d(xpos + width * i, ypos + height);
		glEnd();
		++i;
	}
	glDisable(GL_TEXTURE_2D);
}
