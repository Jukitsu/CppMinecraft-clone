#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include "geometry.h"
#include "blocks/block_type.h"


namespace Rendering
{
	class Mesh
	{
		std::vector<Geometry::Vertex> mesh_data;
		std::vector<unsigned int> mesh_indices;
	public:
		Mesh(unsigned long max_quads);
		~Mesh() noexcept;
		const std::vector<Geometry::Vertex>& getVertexData() const;
		const std::vector<unsigned int>& getIndices() const;
	private:
		inline void pushVertex(const Geometry::Vertex& vertex);
		inline void pushIndex(unsigned int index);
	public:
		void pushQuad(const Geometry::Quad& quad, unsigned int current_quad_count);
		unsigned int pushBlock(const Blocks::BlockType& block_type,
			const glm::vec3& pos, unsigned int current_quad_count);
	};

}