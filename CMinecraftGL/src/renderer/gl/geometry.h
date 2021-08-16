#pragma once
#include <array>


struct Vertex
{
	float position[3];
	float tex_coords[2];
	float tex_index;
	float shading_value;
};

struct Quad
{
	Vertex vertices[4];
};

std::array<unsigned char, 6> quad_indices =
{
   0,  1,  2,  
   0,  2,  3,
};




