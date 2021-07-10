#version 330

out vec4 fragment_colour; 

in vec3 local_position;  
in vec3 interpolated_tex_coords;

uniform sampler2DArray texture_array_sampler;

uniform vec4 lighting;
uniform vec4 overlay;
uniform vec4 shading;

void main(void) {
	vec4 texture_colour = texture(texture_array_sampler, interpolated_tex_coords);
	fragment_colour = (texture_colour * lighting) * shading + overlay;
}