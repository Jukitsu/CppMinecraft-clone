#include "ibo.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


IndexBuffer::IndexBuffer(const void* indices, GLuint size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}