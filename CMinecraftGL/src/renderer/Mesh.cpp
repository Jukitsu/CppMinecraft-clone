#include "Mesh.h"
#include <iostream>

BufferLayout::BufferLayout(unsigned char dim, unsigned char offset)
	:dim(dim), offset(offset * sizeof(float)), stride()
{
}

Mesh::Mesh()
	:vertex_positions_layout(3u, 0u),
	tex_coords_layout(3u, 3u),
	shading_values_layout(1u, 6u)
{
	stride = (vertex_positions_layout.dim
		+ tex_coords_layout.dim
		+ shading_values_layout.dim) * sizeof(float);

	vertex_positions_layout.stride = stride;
	tex_coords_layout.stride = stride;
	shading_values_layout.stride = stride;
}

Mesh::~Mesh() noexcept
{

}
void Mesh::push(const float *data, size_t size)
{
	for (unsigned int i = 0; i < size; i++)
		mesh_data.push_back(data[i]);
}

void Mesh::push_indices(const unsigned short *indices, size_t size)
{
	for (unsigned short i = 0; i < size; i++)
		mesh_indices.push_back(indices[i]);
}