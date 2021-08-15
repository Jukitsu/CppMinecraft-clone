#pragma once
#include <iostream>
#include "renderer/gl/geometry.h"

float cube_vertex_data[168] = {
	/* Vertex Positions */  /* Tex Coords  */		/* Shading */
	 0.5,  0.5,  0.5,       0.0,  0.0,  0.0,		0.8,
	 0.5, -0.5,  0.5,		0.0,  1.0,  0.0,		0.8,
	 0.5, -0.5, -0.5,		1.0,  1.0,  0.0,		0.8,
	 0.5,  0.5, -0.5,		1.0,  0.0,  0.0,		0.8,

	-0.5,  0.5, -0.5,		0.0,  0.0,  0.0,		0.8,
	-0.5, -0.5, -0.5,		0.0,  1.0,  0.0,		0.8,
	-0.5, -0.5,  0.5,		1.0,  1.0,  0.0,		0.8,
	-0.5,  0.5,  0.5,		1.0,  0.0,  0.0,		0.8,

	 0.5,  0.5,  0.5,		0.0,  0.0,  0.0,		1.0,
	 0.5,  0.5, -0.5,		0.0,  1.0,  0.0,		1.0,
	-0.5,  0.5, -0.5,		1.0,  1.0,  0.0,		1.0,
	-0.5,  0.5,  0.5,		1.0,  0.0,  0.0,		1.0,

	-0.5, -0.5,  0.5,		0.0,  0.0,  0.0,		0.4,
	-0.5, -0.5, -0.5,		0.0,  1.0,  0.0,		0.4,
	 0.5, -0.5, -0.5,		1.0,  1.0,  0.0,		0.4,
	 0.5, -0.5,  0.5,		1.0,  0.0,  0.0,		0.4,

	-0.5,  0.5,  0.5,		0.0,  0.0,  0.0,		0.6,
	-0.5, -0.5,  0.5,		0.0,  1.0,  0.0,		0.6,
	 0.5, -0.5,  0.5,		1.0,  1.0,  0.0,		0.6,
	 0.5,  0.5,  0.5,		1.0,  0.0,  0.0,		0.6,

	 0.5,  0.5, -0.5,		0.0,  0.0,  0.0,		0.6,
	 0.5, -0.5, -0.5,		0.0,  1.0,  0.0,		0.6,
	-0.5, -0.5, -0.5,		1.0,  1.0,  0.0,		0.6,
	-0.5,  0.5, -0.5,		1.0,  0.0,  0.0,		0.6,
};


class Model
{
	Quad *quad;
	unsigned int quad_number;
public:
	virtual Quad *get_quads() = 0;
	virtual unsigned char get_quad_number() = 0;
};
	

class Cube : public Model
{
	Quad quad[6];
public:
	Cube()
	{
		errno_t err = memcpy_s(quad, 6 * sizeof(Quad), cube_vertex_data, 168 * sizeof(float));
		// std::cout << err << '\n';
	}
	Quad *get_quads() override
	{
		return quad;
	}
	unsigned char get_quad_number() override
	{
		return 6;
	}
};


