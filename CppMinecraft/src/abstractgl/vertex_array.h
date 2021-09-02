#pragma once
#include "OpenGL.h"

#include "buffers.h"

namespace AbstractGL
{
	class VertexArray {
		GLuint id;
		static const VertexArray* bound;
	public:
		VertexArray() :id()
		{
			glGenVertexArrays(1, &id);
		}
		~VertexArray()
		{
			glDeleteVertexArrays(1, &id);
		}

		void bind() const
		{
			if (bound != this)
			{
				glBindVertexArray(id);
				bound = this;
			}
		}
		void linkAttrib(VertexBuffer* vbo, GLubyte va_index,
			GLubyte data_dim, GLenum type, GLsizei stride, GLubyte offset)
		{
			bind();
			vbo->bind();
			glVertexAttribPointer((GLuint)va_index, (GLint)data_dim,
				GL_FLOAT, GL_FALSE, stride, (const void*)offset);
			glEnableVertexAttribArray(va_index);
		}
	};
}