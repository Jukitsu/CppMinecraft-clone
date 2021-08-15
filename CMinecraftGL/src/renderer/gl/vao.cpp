#include "vao.h"


VertexArray::VertexArray():id(){}


VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &id);
}


inline void VertexArray::init() {
	glGenVertexArrays(1, &id);
}

inline void VertexArray::bind() const {
	glBindVertexArray(id);
}

inline void VertexArray::unbind() const {
	glBindVertexArray(0);
}

inline void VertexArray::link_attrib(VertexBuffer *vbo, GLubyte va_index,
	GLubyte data_dim, GLenum type, GLsizei stride, GLubyte offset) {
	bind();
	vbo->bind();
	glVertexAttribPointer((GLuint)va_index, (GLint)data_dim, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
	glEnableVertexAttribArray(va_index);
}