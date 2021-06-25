#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "glErrors.h"


class VertexBuffer {
public:
	GLuint id;
	VertexBuffer();
	~VertexBuffer();
	void init();
	void sendData(const void* data, GLuint size, GLint data_dim, GLuint va_index);
	void bind();
	void unbind();
};

