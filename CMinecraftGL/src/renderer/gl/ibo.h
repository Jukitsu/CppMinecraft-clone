#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>



class IndexBuffer {
public:
	const void* indices;
	GLuint size;
	GLuint id;
	IndexBuffer(const void* indices, GLuint size);
	~IndexBuffer();
	void bind();
	void unbind();
};

