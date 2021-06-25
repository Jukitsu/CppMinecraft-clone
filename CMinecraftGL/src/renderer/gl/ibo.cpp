#include "ibo.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


IndexBuffer::IndexBuffer():id(){}

IndexBuffer::~IndexBuffer() {
	glCall (glDeleteBuffers(1, &id));
}

void IndexBuffer::init() {
	glCall (glGenBuffers(1, &id));
}

void IndexBuffer::sendIndices(const void* indices, GLuint size) {
	glCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	glCall (glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}

void IndexBuffer::bind() {
	glCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::unbind() {
	glCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}