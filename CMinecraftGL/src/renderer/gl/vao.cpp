#include "vao.h"


VertexArray::VertexArray():id(), vbos(){}


VertexArray::~VertexArray() {
	glCall (glDeleteVertexArrays(1, &id));
}

void VertexArray::init() {
	glCall (glGenVertexArrays(1, &id));
}

void VertexArray::bind() {
	glCall (glBindVertexArray(id));
}

void VertexArray::unbind() {
	glCall (glBindVertexArray(0));
}

void VertexArray::link_attrib(VertexBuffer *vbo, GLint data_dim, GLuint va_index) {
	vbos[va_index] = vbo;
	glCall (glVertexAttribPointer(va_index, data_dim, GL_FLOAT, GL_FALSE, 0, 0));
	glCall (glEnableVertexAttribArray(va_index));
}