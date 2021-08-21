#include "buffers.h"

namespace AbstractGL
{
	// VERTEX BUFFER
	const VertexBuffer* VertexBuffer::bound = nullptr;
	VertexBuffer::VertexBuffer() :id()
	{
		glGenBuffers(1, &id);
	}
	VertexBuffer::~VertexBuffer() noexcept
	{
		glDeleteBuffers(1, &id);
	}
	void VertexBuffer::bufferData(GLuint size)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
	void VertexBuffer::bufferSubData(const void* data, GLuint size, unsigned int offset)
	{
		bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}
	void VertexBuffer::bind() const
	{
		if (bound != this)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			bound = this;
		}
	}

	// INDEX BUFFER
	const IndexBuffer* IndexBuffer::bound = nullptr;
	IndexBuffer::IndexBuffer() : id()
	{
		glGenBuffers(1, &id);
	}
	IndexBuffer::~IndexBuffer() noexcept
	{
		glDeleteBuffers(1, &id);
	}
	void IndexBuffer::bufferData(const void* data, GLuint size)
	{
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void IndexBuffer::bind() const
	{
		if (bound != this)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			bound = this;
		}
	}
}