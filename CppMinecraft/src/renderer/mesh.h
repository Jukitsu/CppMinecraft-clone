#pragma once

#include <vector>
#include <array>
#include <queue>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include "geometry.h"
#include "blocks/block_type.h"
#include "batch_info.h"


namespace Rendering
{

	class Mesh
	{
		const size_t max_quads;
		std::vector<Geometry::Vertex> mesh_data; // !! Load mesh data on initial load 
		size_t max_index_count;
		size_t max_vertex_count;
	public:
		size_t current_quad_count;

		Mesh(size_t max_quads);
		~Mesh() noexcept;

		const std::vector<Geometry::Vertex>& getVertexData() const
		{
			return mesh_data;
		}
		size_t getMaxIndexCount() const
		{
			return max_index_count;
		}
		size_t getMaxVertexCount() const
		{
			return max_vertex_count;
		}
		void clear()
		{
			mesh_data.clear();
			current_quad_count = 0;
		}
	private:
		inline void pushVertex(const Geometry::Vertex& vertex);
	public:
		void pushQuad(const Geometry::Quad& quad);
		void pushBlock(const Blocks::BlockType& block_type,
			const glm::vec3& pos,
			const BatchInfo& batch_info); //Returns the new quad count
	};

}