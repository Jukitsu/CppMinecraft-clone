#version 330

out vec4 fragment_colour; 

in vec3 local_position;  
in vec3 interpolated_tex_coords;
in float interpolated_shading_value;

uniform sampler2DArray texture_array_sampler;



void main(void) {
	vec4 texture_colour = texture(texture_array_sampler, interpolated_tex_coords);
	fragment_colour = texture_colour * interpolated_shading_value;
}