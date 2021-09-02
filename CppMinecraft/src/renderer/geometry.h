#pragma once

#include <array>

namespace Geometry
{
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
	
	const std::array<unsigned int, 6> quad_indices
	{
		0, 1, 2,
		0, 2, 3
	};
}

