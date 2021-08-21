#include "vertex_array.h"

#include <iostream>
namespace AbstractGL
{
	const VertexArray* VertexArray::bound = nullptr;

	VertexArray::VertexArray() :id()
	{
		glGenVertexArrays(1, &id);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::bind() const
	{
		if (bound != this)
		{
			glBindVertexArray(id);
			bound = this;
		}
	}
	void VertexArray::linkAttrib(VertexBuffer* vbo, GLubyte va_index,
		GLubyte data_dim, GLenum type, GLsizei stride, GLubyte offset)
	{
		bind();
		vbo->bind();
		glVertexAttribPointer((GLuint)va_index, (GLint)data_dim,
			GL_FLOAT, GL_FALSE, stride, (const void*)offset);
		glEnableVertexAttribArray(va_index);
	}
}