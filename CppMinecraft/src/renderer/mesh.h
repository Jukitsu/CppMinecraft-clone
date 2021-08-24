#pragma once

#include <vector>
#include <array>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include "geometry.h"
#include "blocks/block_type.h"
#include "batch_info.h"


namespace Rendering
{
	class Mesh
	{
		const unsigned long max_quads;
		std::vector<Geometry::Vertex> mesh_data;
		unsigned int* mesh_indices;
		unsigned int max_index_count;
		unsigned int max_vertex_count;
	public:
		unsigned int current_index_count;

		Mesh(unsigned long max_quads, unsigned int* indices);
		~Mesh() noexcept;

		const std::vector<Geometry::Vertex>& getVertexData() const;
		unsigned int* getIndices() const;
		unsigned int getMaxIndexCount() const;
		unsigned int getMaxVertexCount() const;

	private:
		inline void pushVertex(const Geometry::Vertex& vertex);
	public:
		void clear();
		void pushQuad(const Geometry::Quad& quad, unsigned int current_quad_count);
		unsigned int pushBlock(const Blocks::BlockType& block_type,
			const glm::vec3& pos, unsigned int current_quad_count, const BatchInfo& batch_info);
	};

}