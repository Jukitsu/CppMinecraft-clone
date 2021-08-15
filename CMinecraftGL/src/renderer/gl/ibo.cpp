#include "ibo.h"



IndexBuffer::IndexBuffer():id(){}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &id);
}

inline void IndexBuffer::init() {
	glGenBuffers(1, &id);
}

inline void IndexBuffer::bufferIndices(const void *indices, GLuint size) {
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

inline void IndexBuffer::bind() const {
	if (!is_bound) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		is_bound = true;
	}
}

inline void IndexBuffer::unbind() const {
	if (is_bound) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		is_bound = false;
	}
}