#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "glErrors.h"
#include "vbo.h"


class VertexArray {
public:
	VertexBuffer *vbos[1];
	GLuint id;
	VertexArray();
	~VertexArray();
	void init();
	void bind();
	void unbind();
	void link_attrib(VertexBuffer* vbo, GLint data_dim, GLuint va_index);
};



