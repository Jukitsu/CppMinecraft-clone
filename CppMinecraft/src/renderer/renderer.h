#pragma once

#include <abstractgl/shader.h>
#include <abstractgl/buffers.h>
#include <abstractgl/vertex_array.h>

#include "mesh.h"

namespace Rendering
{
	class Renderer
	{
		AbstractGL::VertexArray vao;
		AbstractGL::VertexBuffer vbo;
		AbstractGL::IndexBuffer ibo;
		AbstractGL::ShaderProgram* shader_program;
		size_t index_count;
	public:
		Renderer();
		~Renderer() noexcept;
		void bufferData(const Mesh& mesh);
		void bindAll() const;
		void bindLayout();
		void clear() const;
		void draw() const;
	};
}