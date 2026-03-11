#include "GLFW/glfw3.h"
#include "gui_draw.h"
#include "board.h"
#include "math.h"

void gui_draw_board(Board_t* board) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			GLdouble xmid = 240.0 + j * 160.0;
			GLdouble ymid = 240.0 + i * 160.0;
			GLubyte r = 0, g = 0, b = 0;
			glColor3ub(r, g, b);
			if (board->board[i][j] == X_) {
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
			else if (board->board[i][j] == O_) {
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
