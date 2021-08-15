#include "Mesh.h"


Mesh::Mesh()
	:current_vertex_data_size(0), index_count(0)
{
	vertices.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6 * 2);
	indices.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6 * 3);
}

Mesh::~Mesh() noexcept
{
}

void Mesh::generate_mesh(Chunk *chunk)
{
	

			
}


void Mesh::push_quad(Quad &&quad, unsigned long quad_count)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		Vertex &vertex = quad.vertices[i];
		push_vertex(std::move(vertex), quad_indices[i] + 4 * quad_count);
	}
}

inline void Mesh::push_vertex(Vertex &&vertex, unsigned long index)
{
	vertices.emplace_back(vertex);
	indices.push_back(index);
}

