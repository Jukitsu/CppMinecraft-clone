#include "renderer.h"

namespace Rendering
{
	using namespace Geometry;
	using namespace AbstractGL;
	
	Renderer::Renderer()
		:vao(), vbo(), ibo(), shader_program(), index_count(0)
	{

	}

	Renderer::~Renderer() noexcept
	{

	}

	void Renderer::bufferData(const Mesh& mesh)
	{
		vao.bind();
		vbo.bufferData(mesh.getVertexData().size() * sizeof(Vertex));
		vbo.bufferSubData(mesh.getVertexData().data(),
			mesh.getVertexData().size() * sizeof(Vertex), 0);
		std::cout << "Size of bufferSubData: " << mesh.getVertexData().size() << '\n';
		ibo.bufferData(mesh.getIndices().data(),
			mesh.getIndices().size() * sizeof(unsigned int));
		index_count = mesh.getIndices().size();
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

	void Renderer::draw() const
	{
		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
	}
}