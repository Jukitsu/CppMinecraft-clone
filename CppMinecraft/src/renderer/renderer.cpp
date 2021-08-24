#include "renderer.h"

namespace Rendering
{
	using namespace Geometry;
	using namespace AbstractGL;
	
	Renderer::Renderer()
		:vao(), vbo(), ibo(), shader_program()
	{

	}

	Renderer::~Renderer() noexcept
	{

	}

	void Renderer::allocateBuffers(const Mesh& mesh)
	{
		vao.bind();
		vbo.bufferData(mesh.getMaxVertexCount() * sizeof(Vertex));
		ibo.bufferData(mesh.getIndices(),
			mesh.getMaxIndexCount() * sizeof(unsigned int));
	}

	void Renderer::bufferBatch(const Mesh& mesh)
	{
		vao.bind();
		vbo.bufferSubData(mesh.getVertexData().data(),
			mesh.getVertexData().size() * sizeof(Vertex), 0);
	}

	void Renderer::bindLayout()
	{
		vao.linkAttrib(&vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
		vao.linkAttrib(&vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coords));
		vao.linkAttrib(&vbo, 2, 1, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, shading_value));
	}

	void Renderer::bindAll() const
	{
		vao.bind();
		vbo.bind();
		ibo.bind();
	}

	void Renderer::draw(unsigned int index_count) const
	{
		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
	}
}