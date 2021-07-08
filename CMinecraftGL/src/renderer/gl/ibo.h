#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "glErrors.h"



class IndexBuffer {
public:
	GLuint id;
	IndexBuffer();
	~IndexBuffer();
	void init();
	void sendIndices(const void *indices, GLuint size);
	void bind();
	void unbind();
};

