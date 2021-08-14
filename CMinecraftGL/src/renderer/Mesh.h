#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <vector>

struct BufferLayout
{
	BufferLayout(unsigned char dim, unsigned char offset);
	unsigned char dim;
	unsigned char offset;
	int stride;
};


class Mesh
{
public:
	std::vector<float> mesh_data;
	std::vector<unsigned short> mesh_indices;
	GLsizei stride;
	BufferLayout vertex_positions_layout;
	BufferLayout tex_coords_layout;
	BufferLayout shading_values_layout;
	Mesh();
	~Mesh() noexcept;
	void push(const float *data, size_t size);
	void push_indices(const unsigned short* indices, size_t size);
};