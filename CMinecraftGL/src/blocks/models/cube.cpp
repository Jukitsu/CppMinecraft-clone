#include "cube.h"


GLfloat cube_vertex_pos[72] = {
	 0.5,  0.5,  0.5,  0.5, -0.5,  0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5,
	-0.5,  0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5,  0.5, -0.5,  0.5,  0.5,
	-0.5,  0.5,  0.5, -0.5,  0.5, -0.5,  0.5,  0.5, -0.5,  0.5,  0.5,  0.5,
	-0.5, -0.5,  0.5, -0.5, -0.5, -0.5,  0.5, -0.5, -0.5,  0.5, -0.5,  0.5,
	-0.5,  0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5,  0.5,  0.5,  0.5,  0.5,
	 0.5,  0.5, -0.5,  0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5,  0.5, -0.5,
};

GLfloat cube_tex_coords[72] = {
	0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  1.0,  1.0,  0.0,  1.0,  0.0,  0.0,
	0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  1.0,  1.0,  0.0,  1.0,  0.0,  0.0,
	0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  1.0,  1.0,  0.0,  1.0,  0.0,  0.0,
	0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  1.0,  1.0,  0.0,  1.0,  0.0,  0.0,
	0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  1.0,  1.0,  0.0,  1.0,  0.0,  0.0,
	0.0,  0.0,  0.0,  0.0,  1.0,  0.0,  1.0,  1.0,  0.0,  1.0,  0.0,  0.0,
};



GLuint cube_indices[36] = {
   0,  1,  2,  0,  2,  3,
	4,  5,  6,  4,  6,  7,
	8,  9, 10,  8, 10, 11,
   12, 13, 14, 12, 14, 15,
   16, 17, 18, 16, 18, 19,
   20, 21, 22, 20, 22, 23,
 };