#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "glErrors.h"


class VertexBuffer {
public:
	GLuint id;
	mutable bool is_bound;
	VertexBuffer();
	~VertexBuffer();
	void init();
	void bufferData(const void* data, GLuint size);
	void bind() const;
	void unbind() const;
};
