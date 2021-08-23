#include "mesh.h"

namespace Rendering
{
	using std::vector;
	using namespace Geometry;
	using namespace Blocks;

	Mesh::Mesh(unsigned long max_quads)
	{
		mesh_data.reserve(max_quads * 4);
		mesh_indices.reserve(max_quads * 6);
	}
	Mesh::~Mesh() noexcept
	{

	}

	const vector<Vertex>& Mesh::getVertexData() const
	{
		return mesh_data;
	}
	const vector<unsigned int>& Mesh::getIndices() const
	{
		return mesh_indices;
	}

	inline void Mesh::pushVertex(const Vertex& vertex)
	{
		mesh_data.push_back(vertex);
	}
	inline void Mesh::pushIndex(unsigned int index)
	{
		mesh_indices.push_back(index);
	}
	
	void Mesh::clear()
	{
		mesh_data.clear();
		mesh_indices.clear();
	}
	void Mesh::pushQuad(const Quad& quad, unsigned int current_quad_count)
	{
		for (const Vertex& vertex : quad.vertices)
		{
			pushVertex(vertex);
		}
		for (unsigned int i = 0; i < 6; i++)
		{
			pushIndex(quad_indices[i] + 4 * current_quad_count);
		}
	}
	unsigned int Mesh::pushBlock(const BlockType& block_type, 
		const glm::vec3& pos, unsigned int current_quad_count)
		/* Returns the new quad count*/
	{
		for (unsigned int i = 0; i < block_type.get_quad_number(); i++)
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
			current_quad_count++;
		}
		return current_quad_count;
	}
}