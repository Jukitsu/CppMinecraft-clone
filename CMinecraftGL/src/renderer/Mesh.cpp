#include "Mesh.h"


Mesh::Mesh()
{
	vertices.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6 * 3); // Reduce realloc()
	indices.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6 * 4);
}

Mesh::~Mesh() noexcept
{
}

void Mesh::generate_mesh(Chunk *chunk)
{
	unsigned int quad_count = 0;
	vertices.clear();
	indices.clear();
	for (unsigned int local_x = 0; local_x < CHUNK_WIDTH; local_x++)
		for (unsigned int local_y = 0; local_y < CHUNK_HEIGHT; local_y++)
			for (unsigned int local_z = 0; local_z < CHUNK_HEIGHT; local_z++)
			{
				BlockID block = chunk->get_block(local_x, local_y, local_z);
				if (!block)
					continue;

				/* Continue writing stuff here */

			}
}

void Mesh::push_face(unsigned char face_number)
{
	/* Use this->push_quad(quad, count ?)*/
	push_quad()
}

void Mesh::push_quad(Quad &&quad, unsigned long quad_count)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		Vertex &vertex = quad.vertices[i];
		push_vertex(std::move(vertex), quad_indices[i] + 4 * quad_count); // This code does not make sense
	}
}

inline void Mesh::push_vertex(Vertex &&vertex, unsigned long index)
{
	vertices.emplace_back(vertex);
	indices.push_back(index);
}

