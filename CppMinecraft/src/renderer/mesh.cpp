#include "mesh.h"

namespace Rendering
{
	using std::vector;
	using namespace Geometry;
	using namespace Blocks;

	Mesh::Mesh(unsigned long max_quads)
		:max_quads(max_quads),
		current_quad_count(0)
	{
		max_vertex_count = max_quads * 4;
		max_index_count = max_quads * 6;
		mesh_data.reserve(max_vertex_count);
	}
	Mesh::~Mesh() noexcept
	{

	}

	inline void Mesh::pushVertex(const Vertex& vertex)
	{
		mesh_data.push_back(vertex);
	}
	
	void Mesh::pushQuad(const Quad& quad)
	{
		for (const Vertex& vertex : quad.vertices)
		{
			pushVertex(vertex);
		}
		current_quad_count++;
	}
	void Mesh::pushBlock(const BlockType& block_type, 
		const glm::vec3& pos, const BatchInfo& batch_info)
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
				pushQuad(current_quad);
			}
		}
	}
}