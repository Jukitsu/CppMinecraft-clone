#version 330

layout(location = 0) in vec3 vertex_position; 

out vec3 local_position;

uniform mat4 matrix;


void main(void) {
	local_position = vertex_position;
	gl_Position = matrix * vec4(vertex_position, 1.0);
}