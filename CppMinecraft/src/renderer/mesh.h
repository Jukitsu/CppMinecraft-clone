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
	struct BatchedVertices
	{
		std::vector<Geometry::Vertex> vertices; // Batched vertices
		size_t offset; // Offset for glSubData
	};

	/* Tracker of the mesh blocks */
	struct MeshBlock 
	{
		glm::vec3 position; // Position
		size_t offset; // Offset of the existing block in the VBO in bytes
		size_t size; // Size of the Block Data in bytes
	};

	class Mesh
	{
		const unsigned long max_quads;
		std::vector<Geometry::Vertex> mesh_data; // !! Load mesh data on initial load 
		unsigned int max_index_count;
		unsigned int max_vertex_count;
	public:
		unsigned int current_quad_count;

		Mesh(unsigned long max_quads);
		~Mesh() noexcept;

		const std::vector<Geometry::Vertex>& getVertexData() const
		{
			return mesh_data;
		}
		unsigned int getMaxIndexCount() const
		{
			return max_index_count;
		}
		unsigned int getMaxVertexCount() const
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