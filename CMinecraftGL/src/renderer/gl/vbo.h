#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>



class VertexBuffer {
public:
	GLuint id;
	const void* data;
	GLuint size;
	GLint data_dim;
	GLuint attr_index;
	VertexBuffer(const void* data, GLuint size, GLint data_dim, GLuint attr_index);
	~VertexBuffer();
	void bind();
	void unbind();
};

