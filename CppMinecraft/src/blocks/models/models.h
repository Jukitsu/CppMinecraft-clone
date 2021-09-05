#pragma once

#include <memory>

#include "renderer/geometry.h"


namespace Blocks
{
	namespace Models
	{
		
		static Geometry::Quad cube_vertex_data[6] = {
			/* Vertex Positions */  /* Tex Coords  */		/* Shading */
			{{
				{ { 0.5,  0.5,  0.5 },      { 0u },  { 0u }, 		{ 0.8 } },
				{ { 0.5, -0.5,  0.5 },		{ 1u },  { 0u },		{ 0.8 } },
				{ { 0.5, -0.5, -0.5 },		{ 2u },  { 0u },		{ 0.8 } },
				{ { 0.5,  0.5, -0.5 },		{ 3u },  { 0u },		{ 0.8 } }
			}},
			{{
				{ {-0.5,  0.5, -0.5 },		{ 0u },  { 0u },		{ 0.8 } },
				{ {-0.5, -0.5, -0.5 },		{ 1u },  { 0u },		{ 0.8 } },
				{ {-0.5, -0.5,  0.5 },		{ 2u },  { 0u },		{ 0.8 } },
				{ {-0.5,  0.5,  0.5 },		{ 3u },  { 0u },		{ 0.8 } },
			}},
			{{
				{ { 0.5,  0.5,  0.5 },		{ 0u },  { 0u },		{ 1.0 } },
				{ { 0.5,  0.5, -0.5 },		{ 1u },  { 0u },		{ 1.0 } },
				{ {-0.5,  0.5, -0.5 },		{ 2u },  { 0u },		{ 1.0 } },
				{ {-0.5,  0.5,  0.5 },		{ 3u },  { 0u },		{ 1.0 } },
			}},
			{{
				{ {-0.5, -0.5,  0.5 },		{ 0u },  { 0u },		{ 0.4 } },
				{ {-0.5, -0.5, -0.5 },		{ 1u },  { 0u },		{ 0.4 } },
				{ { 0.5, -0.5, -0.5 },		{ 2u },  { 0u },		{ 0.4 } },
				{ { 0.5, -0.5,  0.5 },		{ 3u },  { 0u },		{ 0.4 } },
			}},
			{{
				{ { -0.5,  0.5,  0.5 },		{ 0u },  { 0u },		{ 0.6 } },
				{ { -0.5, -0.5,  0.5 },		{ 1u },  { 0u },		{ 0.6 } },
				{ { 0.5, -0.5,  0.5 },		{ 2u },  { 0u },		{ 0.6 } },
				{ { 0.5,  0.5,  0.5 },		{ 3u },  { 0u },		{ 0.6 } },
			}},
			{{
				{ { 0.5,  0.5, -0.5 },		{ 0u },  { 0u },		{ 0.6 } },
				{ { 0.5, -0.5, -0.5 },		{ 1u },  { 0u },		{ 0.6 } },
				{ {-0.5, -0.5, -0.5 },		{ 2u },  { 0u },		{ 0.6 } },
				{ {-0.5,  0.5, -0.5 },		{ 3u },  { 0u },		{ 0.6 } },
			}}
		};
		

		class Model
		{
		protected:
			Geometry::Quad* quads;
		public:
			virtual const Geometry::Quad* get_quads() const = 0;
			virtual uint16_t get_quad_number() const = 0;
		};

		class Air : public Model
		{
		public:
			const Geometry::Quad* get_quads() const override
			{
				return nullptr;
			}
			uint16_t get_quad_number() const override
			{
				return 0;
			}
		};

		class Cube : public Model
		{
			Geometry::Quad *quads;
		public:
			Cube()
				:quads(cube_vertex_data)
			{
				
			}
			const Geometry::Quad* get_quads() const override
			{
				return quads;
			}
			uint16_t get_quad_number() const override
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