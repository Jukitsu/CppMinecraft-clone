#include "vbo.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


VertexBuffer::VertexBuffer(const void* data, GLuint size, GLint data_dim, GLuint va_index)
	:attr_index(va_index), data(data), size(size), data_dim(data_dim)
{
	glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

void VertexBuffer::modifyData(const void* data, GLuint size) {
	this->data = data; this->size = size;
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attr_index, data_dim, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attr_index);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
