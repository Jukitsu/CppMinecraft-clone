#version 330 core

layout(location = 0) in vec3 vertex_position; 
layout(location = 1) in uint tex_UV_index;
layout(location = 2) in uint tex_index;
layout(location = 3) in float shading_value;


out vec3 v_tex_coords;
out float v_shading_value;

uniform mat4 mvp;

vec2 tex_coords[4] = vec2[4]
(
	vec2(0.0f,  1.0f),
	vec2(0.0f,  0.0f),
	vec2(1.0f,  0.0f),
	vec2(1.0f,  1.0f)
);

void main(void) {
	v_tex_coords = vec3(tex_coords[uint(tex_UV_index)], tex_index);
	v_shading_value = shading_value;

	gl_Position = mvp * vec4(vertex_position, 1.0);
}