#include "vbo.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


VertexBuffer::VertexBuffer():id(){}

VertexBuffer::~VertexBuffer() {
	glCall (glDeleteBuffers(1, &id));
}

void VertexBuffer::init() {
	glCall (glGenBuffers(1, &id));
}

void VertexBuffer::sendData(const void* data, GLuint size) {
	glCall (glBindBuffer(GL_ARRAY_BUFFER, id));
	glCall (glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::bind() {
	glCall (glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::unbind() {
	glCall (glBindBuffer(GL_ARRAY_BUFFER, 0));
}


