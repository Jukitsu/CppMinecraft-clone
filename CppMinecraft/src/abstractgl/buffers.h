#pragma once
#include "OpenGL.h"
#include <iostream>

namespace AbstractGL
{
	class VertexBuffer
	{
		GLuint id;
		static const VertexBuffer* bound;
	public:
		GLuint current_size;
		VertexBuffer()
			:id(0), current_size(0)
		{
			glGenBuffers(1, &id);
		}
		~VertexBuffer() noexcept
		{
			glDeleteBuffers(1, &id);
		}
		void allocate(GLuint size)
		{
			bind();
			current_size = size;
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		}
		void bufferSubData(const void* data, GLuint size, GLintptr offset)
		{
			bind();
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}
		void bind() const
		{
			if (bound != this)
			{
				glBindBuffer(GL_ARRAY_BUFFER, id);
				bound = this;
			}
		}
	};

	class IndexBuffer 
	{
		GLuint id;
		const static IndexBuffer* bound;
	public:
		IndexBuffer()
		{
			glGenBuffers(1, &id);
		}
		~IndexBuffer() noexcept
		{
			glDeleteBuffers(1, &id);
		}
		void bufferData(const void* data, GLuint size)
		{
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}
		void bind() const
		{
			if (bound != this)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
				bound = this;
			}
		}
	};

}