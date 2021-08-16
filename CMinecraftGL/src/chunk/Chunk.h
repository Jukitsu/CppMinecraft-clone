#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "renderer/Renderer.h"
#include "renderer/Mesh.h"
#include "utility.h"


class Chunk
{
	Position position;
	BlockID blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH];
	Renderer chunk_renderer;
	Mesh mesh;
public:
	Chunk();
	~Chunk();
	const Position &get_position() const;
	const BlockID get_block(const Vector3D &pos) const;
	const BlockID get_block(const int x, const int y, const int z) const;
	void set_block(const Vector3D &pos, BlockID block);
	void set_block(const int x, const int y, const int z, BlockID block);
	void update_mesh();
	void render();
};