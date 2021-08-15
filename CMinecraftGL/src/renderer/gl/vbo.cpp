#include "vbo.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


VertexBuffer::VertexBuffer():id(), is_bound(false){}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

inline void VertexBuffer::init() {
	glGenBuffers(1, &id);
}

inline void VertexBuffer::bufferData(const void *data, GLuint size)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

inline void VertexBuffer::bind() const {
	if (!is_bound)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		is_bound = true;
	}
}

inline void VertexBuffer::unbind() const {
	if (is_bound)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		is_bound = false;
	}
}


