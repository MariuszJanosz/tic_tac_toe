#ifndef FONT_ATLAS_H
#define FONT_ATLAS_H

#include "GLFW/glfw3.h"

typedef struct {
	GLubyte RGBA[256 * 256 * 4];
} Font_atlas_data_t;

extern GLuint font_atlas_tex;
extern Font_atlas_data_t* font_atlas_data;

#endif //FONT_ATLAS_H