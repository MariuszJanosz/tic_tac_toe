#include "GLFW/glfw3.h"
#include "gui_draw.h"
#include "board.h"
#include "math.h"
#include "font_atlas.h"
#include "phases.h"

#define PI 3.141592

static double ABS(double x) {
	if (x >= 0.0) return x;
	return -x;
}

static void draw_cell_boundary(GLdouble xmid, GLdouble ymid, GLdouble cell_w, GLdouble cell_h) {
	glBegin(GL_LINE_LOOP);
	glVertex2d(xmid - cell_w / 2, ymid - cell_h / 2);
	glVertex2d(xmid - cell_w / 2, ymid + cell_h / 2);
	glVertex2d(xmid + cell_w / 2, ymid + cell_h / 2);
	glVertex2d(xmid + cell_w / 2, ymid - cell_h / 2);
	glEnd();
}

static void draw_X(GLdouble xmid, GLdouble ymid, GLdouble arm_len_sqrt2) {
	double half_thickness = 2.0 * sqrt(2.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(xmid, ymid);
	glVertex2d(xmid - half_thickness, ymid);
	glVertex2d(xmid - arm_len_sqrt2 - half_thickness, ymid - arm_len_sqrt2);
	glVertex2d(xmid - arm_len_sqrt2, ymid - arm_len_sqrt2 - half_thickness);
	glVertex2d(xmid, ymid - half_thickness);
	glVertex2d(xmid + arm_len_sqrt2, ymid - arm_len_sqrt2 - half_thickness);
	glVertex2d(xmid + arm_len_sqrt2 + half_thickness, ymid - arm_len_sqrt2);
	glVertex2d(xmid + half_thickness, ymid);
	glVertex2d(xmid + arm_len_sqrt2 + half_thickness, ymid + arm_len_sqrt2);
	glVertex2d(xmid + arm_len_sqrt2, ymid + arm_len_sqrt2 + half_thickness);
	glVertex2d(xmid, ymid + half_thickness);
	glVertex2d(xmid - arm_len_sqrt2, ymid + arm_len_sqrt2 + half_thickness);
	glVertex2d(xmid - arm_len_sqrt2 - half_thickness, ymid + arm_len_sqrt2);
	glVertex2d(xmid - half_thickness, ymid);
	glEnd();
}

static void draw_O(GLdouble xmid, GLdouble ymid, GLdouble R) {
	double half_thickness = 2.0;
	glBegin(GL_TRIANGLE_STRIP);
#define CIRCEL_STEPS 32
	for (int i = 0; i <= CIRCEL_STEPS; ++i) {
		double unit_vec_x = cos(2 * PI * i / CIRCEL_STEPS);
		double unit_vec_y = sin(2 * PI * i / CIRCEL_STEPS);
		glVertex2d(xmid + (R + half_thickness) * unit_vec_x, ymid + (R + half_thickness) * unit_vec_y);
		glVertex2d(xmid + (R - half_thickness) * unit_vec_x, ymid + (R - half_thickness) * unit_vec_y);
	}
#undef CIRCLE_STEPS
	glEnd();
}

static void animate_color_transition(	Animation_t* animation, unsigned long long dt, double (*transition)(double),
										GLubyte r_start, GLubyte g_start, GLubyte b_start,
										GLubyte r_end, GLubyte g_end, GLubyte b_end) {
	animation->time_elapsed += dt;
	if (animation->time_elapsed >= animation->time) {
		animation->is_animating = 0;
	}
	double param = (double)animation->time_elapsed / animation->time;
	if (param > 1.0) {
		param = 1.0;
	}
	double t = transition(param);
	GLubyte r = (GLubyte)(255 * (1.0 - t) * r_start + t * r_end);
	GLubyte g = (GLubyte)(255 * (1.0 - t) * g_start + t * g_end);
	GLubyte b = (GLubyte)(255 * (1.0 - t) * b_start + t * b_end);
	glColor3ub(r, g, b);
}

static double ABS_cos_3_2_pi(double param) {
	return ABS(cos(PI * 1.5 * param));
}

static void draw_winning_lines(Game_t* game) {
	int winning_lines[2];
	int winnig_lines_count = 0;
	detect_winning_lines(&game->board, winning_lines, &winnig_lines_count);
	for (int i = 0; i < winnig_lines_count; ++i) {
		GLdouble xmid_start = 0.0;
		GLdouble ymid_start = 0.0;
		GLdouble xmid_end = 0.0;
		GLdouble ymid_end = 0.0;
		switch (winning_lines[i]) {
		case FIRST_ROW:
			xmid_start = 240.0 + 0 * 160.0;
			ymid_start = 240.0 + 0 * 160.0;
			xmid_end = 240.0 + 2 * 160.0;
			ymid_end = 240.0 + 0 * 160.0;
			break;
		case SECOND_ROW:
			xmid_start = 240.0 + 0 * 160.0;
			ymid_start = 240.0 + 1 * 160.0;
			xmid_end = 240.0 + 2 * 160.0;
			ymid_end = 240.0 + 1 * 160.0;
			break;
		case THITD_ROW:
			xmid_start = 240.0 + 0 * 160.0;
			ymid_start = 240.0 + 2 * 160.0;
			xmid_end = 240.0 + 2 * 160.0;
			ymid_end = 240.0 + 2 * 160.0;
			break;
		case FIRST_COLUMN:
			xmid_start = 240.0 + 0 * 160.0;
			ymid_start = 240.0 + 0 * 160.0;
			xmid_end = 240.0 + 0 * 160.0;
			ymid_end = 240.0 + 2 * 160.0;
			break;
		case SECOND_COLUMN:
			xmid_start = 240.0 + 1 * 160.0;
			ymid_start = 240.0 + 0 * 160.0;
			xmid_end = 240.0 + 1 * 160.0;
			ymid_end = 240.0 + 2 * 160.0;
			break;
		case THIRD_COLUMN:
			xmid_start = 240.0 + 2 * 160.0;
			ymid_start = 240.0 + 0 * 160.0;
			xmid_end = 240.0 + 2 * 160.0;
			ymid_end = 240.0 + 2 * 160.0;
			break;
		case MAIN_DIAGONAL:
			xmid_start = 240.0 + 0 * 160.0;
			ymid_start = 240.0 + 0 * 160.0;
			xmid_end = 240.0 + 2 * 160.0;
			ymid_end = 240.0 + 2 * 160.0;
			break;
		case COUNTERDIAGONAL:
			xmid_start = 240.0 + 2 * 160.0;
			ymid_start = 240.0 + 0 * 160.0;
			xmid_end = 240.0 + 0 * 160.0;
			ymid_end = 240.0 + 2 * 160.0;
			break;
		default:
			break;
		}
		glColor3ub(0, 0, 0);
		double half_thickness = 2.0;
		if (winning_lines[i] == MAIN_DIAGONAL) {
			glBegin(GL_QUADS);
			glVertex2d(xmid_start + half_thickness, ymid_start - half_thickness);
			glVertex2d(xmid_end + half_thickness, ymid_end - half_thickness);
			glVertex2d(xmid_end - half_thickness, ymid_end + half_thickness);
			glVertex2d(xmid_start - half_thickness, ymid_start + half_thickness);
			glEnd();
		}
		else {
			glBegin(GL_QUADS);
			glVertex2d(xmid_start + half_thickness, ymid_start + half_thickness);
			glVertex2d(xmid_end + half_thickness, ymid_end + half_thickness);
			glVertex2d(xmid_end - half_thickness, ymid_end - half_thickness);
			glVertex2d(xmid_start - half_thickness, ymid_start - half_thickness);
			glEnd();
		}
	}
}

void gui_draw_board(Game_t* game) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			GLdouble xmid = 240.0 + j * 160.0;
			GLdouble ymid = 240.0 + i * 160.0;
			GLdouble cell_w = 160.0, cell_h = 160.0;
			glColor3ub(0, 0, 0);
			//Draw cell boundary
			draw_cell_boundary(xmid, ymid, cell_w, cell_h);
			//If cell is occupied draw appropriate letter
			if (game->board.board[i][j] == X_) {
				if (game->phase->animations[3 * i + j].is_animating) {
					animate_color_transition(&game->phase->animations[3 * i + j], game->dt, ABS_cos_3_2_pi,
						0, 0, 0,
						0, 255, 0);
				}
				GLdouble arm_len_sqrt2 = 40.0;
				draw_X(xmid, ymid, arm_len_sqrt2);
				glColor3ub(0, 0, 0);
			}
			else if (game->board.board[i][j] == O_) {
				if (game->phase->animations[3 * i + j].is_animating) {
					animate_color_transition(&game->phase->animations[3 * i + j], game->dt, ABS_cos_3_2_pi,
						0, 0, 0,
						0, 0, 255);
				}
				GLdouble R = 40.0;
				draw_O(xmid, ymid, R);
				glColor3ub(0, 0, 0);
			}
		}
	}
	if (game->is_over) {
		draw_winning_lines(game);
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
