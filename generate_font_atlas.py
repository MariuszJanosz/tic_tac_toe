import os
import sys
import io
import re
import imageio.v3 as iio

def write_data_line(out_file, image, line_id, width, height, channels):
	line = img[line_id]
	for col in range(width):
		for ch in range(channels):
			out_file.write(str(line[col][ch]))
			if line_id != (height - 1) or col != (width - 1) or ch != (channels - 1):
				out_file.write(',')
		out_file.write(' ')
	out_file.write('\n')

file_path = os.path.abspath(sys.argv[1])
img_path =  os.path.abspath(sys.argv[2])

f = io.open(file_path, 'w')
img = iio.imread(img_path)
width = img.shape[1]
height = img.shape[0]
channels = img.shape[2]
size = width * height * channels

f.write('#include "font_atlas.h"\n')
f.write('\n')
f.write('GLuint font_atlas_tex;\n')
f.write('Font_atlas_data_t __font_atlas_data__ = {\n')
f.write(f'.width = {width},\n')
f.write(f'.height = {height},\n')
f.write(f'.channels = {channels},\n')
f.write('.RGBA = {\n')
for line_id in range(height):
	write_data_line(f, img, line_id, width, height, channels)
f.write('}};\n')
f.write('\n')
f.write('Font_atlas_data_t* font_atlas_data = &__font_atlas_data__;\n')
f.close()

h_file_path = re.sub('.c$', '.h', file_path)
f_h = io.open(h_file_path, 'w')
f_h.write('#ifndef FONT_ATLAS_H\n')
f_h.write('#define FONT_ATLAS_H\n')
f_h.write('\n')
f_h.write('#include "GLFW/glfw3.h"\n')
f_h.write('\n')
f_h.write(f'#define ATLAS_WIDTH {width}\n')
f_h.write(f'#define ATLAS_HEIGHT {height}\n')
f_h.write(f'#define ATLAS_CHANNELS {channels}\n')
f_h.write('\n')
f_h.write('typedef struct {\n')
f_h.write('	int width, height, channels;\n')
f_h.write('	GLubyte RGBA[ATLAS_WIDTH * ATLAS_HEIGHT * ATLAS_CHANNELS];\n')
f_h.write('} Font_atlas_data_t;\n')
f_h.write('\n')
f_h.write('extern GLuint font_atlas_tex;\n')
f_h.write('extern Font_atlas_data_t* font_atlas_data;\n')
f_h.write('\n')
f_h.write('#endif //FONT_ATLAS_H\n')
f_h.close()