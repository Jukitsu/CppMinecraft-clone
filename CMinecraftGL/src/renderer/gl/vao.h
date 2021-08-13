#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "glErrors.h"
#include "vbo.h"


class VertexArray {
public:
	GLuint id;
	VertexArray();
	~VertexArray();
	void init();
	void bind() const;
	void unbind() const;
	void link_attrib(VertexBuffer *vbo, GLuint va_index, 
		unsigned short data_dim, GLenum type, GLsizei stride, int offset);
};



