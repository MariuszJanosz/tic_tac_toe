import os
import sys
import io
import imageio.v3 as iio

def write_data_line(out_file, image, i):
	line = img[i]
	for j in range(256):
		out_file.write(str(line[j][0]))
		out_file.write(',')
		out_file.write(str(line[j][1]))
		out_file.write(',')
		out_file.write(str(line[j][2]))
		out_file.write(',')
		out_file.write(str(line[j][3]))
		if i != 255 or j != 255:
			out_file.write(', ')
	out_file.write('\n')

file_path = os.path.abspath(sys.argv[1])
img_path =  os.path.abspath(sys.argv[2])

f = io.open(file_path, 'w')
img = iio.imread(img_path, mode="RGBA")

f.write('#include "font_atlas.h"\n')
f.write('\n')
f.write('GLuint font_atlas_tex;\n')
f.write('Font_atlas_data_t __font_atlas_data__ = {.RGBA = {\n')
for i in range(256):
	write_data_line(f, img, i)
f.write('}};\n')
f.write('\n')
f.write('Font_atlas_data_t* font_atlas_data = &__font_atlas_data__;\n')
f.close()
