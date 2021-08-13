#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <vector>

struct BufferLayout
{
	BufferLayout(unsigned short dim, unsigned short offset);
	unsigned short dim;
	short offset;
	int stride;
};



class Mesh
{
public:
	std::vector<float> mesh_data;
	std::vector<unsigned int> mesh_indices;
	GLsizei stride;
	BufferLayout vertex_positions_layout;
	BufferLayout tex_coords_layout;
	BufferLayout shading_values_layout;
	Mesh();
	~Mesh() noexcept;
	void push(const float *data, size_t size);
	void push_indices(const unsigned int* indices, size_t size);
};