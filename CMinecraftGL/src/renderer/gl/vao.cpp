#include "vao.h"


VertexArray::VertexArray():id(){}


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

void VertexArray::link_attrib(VertexBuffer *vbo, GLuint va_index, GLint data_dim, GLenum type, GLsizei stride, int offset) {
	bind();
	vbo->bind();
	glCall (glVertexAttribPointer(va_index, data_dim, GL_FLOAT, GL_FALSE, stride, (const void*)offset));
	glCall (glEnableVertexAttribArray(va_index));
}