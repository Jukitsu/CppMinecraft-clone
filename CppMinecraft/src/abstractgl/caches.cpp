#include "buffers.h"
#include "shader.h"
#include "texture_array.h"
#include "vertex_array.h"

namespace AbstractGL
{
	// caching initialization
	const VertexBuffer* VertexBuffer::bound = nullptr;
	
	const IndexBuffer* IndexBuffer::bound = nullptr;

	const VertexArray* VertexArray::bound = nullptr;

	const ShaderProgram* ShaderProgram::used = nullptr;

	const TextureArray* TextureArray::bound = nullptr;
	
}