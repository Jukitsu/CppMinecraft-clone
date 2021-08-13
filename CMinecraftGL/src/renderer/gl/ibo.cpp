#include "ibo.h"



IndexBuffer::IndexBuffer():id(){}

IndexBuffer::~IndexBuffer() {
	glCall (glDeleteBuffers(1, &id));
}

void IndexBuffer::init() {
	glCall (glGenBuffers(1, &id));
}

void IndexBuffer::sendIndices(const void *indices, GLuint size) {
	glCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	glCall (glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}

void IndexBuffer::bind() const {
	glCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::unbind() const{
	glCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}