#pragma once

#include <memory>

#include "renderer/geometry.h"


namespace Blocks
{
	namespace Models
	{
		static float cube_vertex_data[168] = {
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
		protected:
			Geometry::Quad* quads;
		public:
			virtual const Geometry::Quad* get_quads() const = 0;
			virtual constexpr unsigned int get_quad_number() const = 0;
		};

		class Air : public Model
		{
		public:
			const Geometry::Quad* get_quads() const override
			{
				return nullptr;
			}
			constexpr unsigned int get_quad_number() const override
			{
				return 0;
			}
		};

		class Cube : public Model
		{
			Geometry::Quad quads[6];
		public:
			Cube()
			{
				memcpy(quads, cube_vertex_data, sizeof(quads));
			}
			const Geometry::Quad* get_quads() const override
			{
				return quads;
			}
			constexpr unsigned int get_quad_number() const override
			{
				return 6;
			}
		};

		struct BlockModels
		{
			Cube cube;
			Air air;
		};

	}
}