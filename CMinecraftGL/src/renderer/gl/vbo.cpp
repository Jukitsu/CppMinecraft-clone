#include "vbo.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


VertexBuffer::VertexBuffer(const void* data, GLuint size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::genVertexAttrib(GLuint va_pointer, GLint pointer_size) 
{
	this->attr_pointer = va_pointer;
	glVertexAttribPointer(attr_pointer, pointer_size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attr_pointer);
}
