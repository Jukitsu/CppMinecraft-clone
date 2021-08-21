#pragma once
#include "OpenGL.h"

#include "buffers.h"

namespace AbstractGL
{
	class VertexArray {
		GLuint id;
		const static VertexArray* bound;
	public:
		VertexArray();
		~VertexArray() noexcept;
		void bind() const;
		void linkAttrib(VertexBuffer* vbo, GLubyte va_index,
			GLubyte data_dim, GLenum type, GLsizei stride, GLubyte offset);
	};
}