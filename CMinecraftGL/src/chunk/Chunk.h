#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "renderer/Renderer.h"
#include "renderer/Mesh.h"
#include "utility.h"


typedef unsigned int BlockID;

class Chunk
{
	BlockID blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH];
	Renderer chunk_renderer;
	Mesh mesh;
public:
	Chunk();
	~Chunk();
	void update_mesh();
	void render();
};