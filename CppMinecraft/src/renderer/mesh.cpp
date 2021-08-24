#include "mesh.h"

namespace Rendering
{
	using std::vector;
	using namespace Geometry;
	using namespace Blocks;

	Mesh::Mesh(unsigned long max_quads, unsigned int* indices)
		:max_quads(max_quads), mesh_indices(indices),
		current_index_count(0)
	{
		max_vertex_count = max_quads * 4;
		max_index_count = max_quads * 6;
		mesh_data.reserve(max_vertex_count);
	}
	Mesh::~Mesh() noexcept
	{

	}

	const vector<Vertex>& Mesh::getVertexData() const
	{
		return mesh_data;
	}
	unsigned int* Mesh::getIndices() const
	{
		return mesh_indices;
	}
	unsigned int Mesh::getMaxIndexCount() const
	{
		return max_index_count;
	}
	unsigned int Mesh::getMaxVertexCount() const
	{
		return max_vertex_count;
	}

	inline void Mesh::pushVertex(const Vertex& vertex)
	{
		mesh_data.push_back(vertex);
	}
	
	void Mesh::clear()
	{
		mesh_data.clear();
		current_index_count = 0;
	}
	void Mesh::pushQuad(const Quad& quad, unsigned int current_quad_count)
	{
		for (const Vertex& vertex : quad.vertices)
		{
			pushVertex(vertex);
		}
		current_index_count += 6;
	}
	unsigned int Mesh::pushBlock(const BlockType& block_type, 
		const glm::vec3& pos, unsigned int current_quad_count, const BatchInfo& batch_info)
		/* Returns the new quad count*/
	{
		bool* batch_info_array = (bool*)&batch_info;
		for (unsigned int i = 0; i < block_type.get_quad_number(); i++)
		{
			if (batch_info_array[i < 6 ? i : 0])
			{
				Quad current_quad;
				memcpy(&current_quad,
					block_type.get_quads() + i % block_type.get_quad_number(),
					sizeof(Quad));
				for (Vertex& vertex : current_quad.vertices)
				{
					vertex.position[0] += pos.x;
					vertex.position[1] += pos.y;
					vertex.position[2] += pos.z;
				}
				pushQuad(current_quad, current_quad_count);
			}
		}
		return current_quad_count;
	}
}