#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <array>
#include "util/glm/glm.hpp"
#include "gl/geometry.h"
#include "utility.h"
#include <vector>
#include "chunk/chunk.h"




class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned long> indices;
	Mesh();
	~Mesh() noexcept;
	void generate_mesh(Chunk *chunk);
	void push_face(Direction &direction);
	void push_quad(Quad &&quad, unsigned long quad_count);
	void push_quads(Quad *quad, unsigned long quad_count);
	void push_vertex(Vertex &&vertex, unsigned long index);
};