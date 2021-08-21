#pragma once
#include "OpenGL.h"

namespace AbstractGL
{
	class VertexBuffer
	{
		GLuint id;
		const static VertexBuffer* bound;
	public:
		VertexBuffer();
		~VertexBuffer() noexcept;
		void bufferData(GLuint size);
		void bufferSubData(const void* data, GLuint size, unsigned int offset);
		void bind() const;
	};

	class IndexBuffer 
	{
		GLuint id;
		const static IndexBuffer* bound;
	public:
		IndexBuffer();
		~IndexBuffer() noexcept;
		void bufferData(const void* data, GLuint size);
		void bind() const;
	};

}