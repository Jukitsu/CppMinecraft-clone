#version 330

out vec4 fragment_colour; 

in vec3 local_position;  

uniform vec4 color_on;
uniform vec4 overlay;
uniform vec4 shading;

void main(void) {
	fragment_colour = (vec4(local_position / 2.0 + 0.5, 1.0) + color_on) * shading + overlay;
}