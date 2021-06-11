#include "ibo.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


IndexBuffer::IndexBuffer(const void* indices, GLuint size)
	:indices(indices), size(size)
{
	glGenBuffers(1, &id);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &id);
}

void IndexBuffer::modifyIndices(const void* indices, GLuint size) {
	this->indices = indices; this->size = size;
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}