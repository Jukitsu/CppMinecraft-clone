#pragma once

#include <memory>

#include "renderer/geometry.h"


namespace Blocks
{
	namespace Models
	{
		class Model
		{
			Geometry::Quad* quads;
			unsigned int quad_number;
		public:
			virtual const Geometry::Quad* get_quads() const = 0;
			virtual unsigned int get_quad_number() const = 0;
		};

		class Cube : public Model
		{
			Geometry::Quad quads[6];
		public:
			Cube();
			const Geometry::Quad* get_quads() const override;
			unsigned int get_quad_number() const override;
		};

		struct BlockModels
		{
			Cube cube;
		};

	}
}