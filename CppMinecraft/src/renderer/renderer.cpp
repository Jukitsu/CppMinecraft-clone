#include "renderer.h"

namespace Rendering
{
	/* Wrapper for the Chunk Renderers
	* Holds the VAO, VBO and IBOs and a 
	* pointer to the shaders
	* Use Batch Rendering and Abstracted OpenGL API
	* to make things easier
	*/
	using namespace Geometry;
	using namespace AbstractGL;
	
	Renderer::Renderer()
		:vao(), vbo(), ibo(), shader_program()
	{

	}

	Renderer::~Renderer() noexcept
	{

	}
	/* Allocate the Vertex Buffer and pass the Indices */
	void Renderer::allocateBuffers(const Mesh& mesh)
	{
		vao.bind();
		vbo.bufferData(mesh.getMaxVertexCount() * sizeof(Vertex));
		ibo.bufferData(mesh.getIndices(),
			mesh.getMaxIndexCount() * sizeof(unsigned int));
	}
	/* Push the batched data to the Vertex Buffer */
	void Renderer::bufferBatch(const Mesh& mesh)
	{
		vao.bind();
		vbo.bufferSubData(mesh.getVertexData().data(),
			mesh.getVertexData().size() * sizeof(Vertex), 0);
	}
	/* Bind the Vertex Attributes to the VAOs with the specified layout:
	* posX, posY, posZ, texX, texY, texZ, shading_value
	*/
	void Renderer::bindLayout()
	{
		vao.linkAttrib(&vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
		vao.linkAttrib(&vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coords));
		vao.linkAttrib(&vbo, 2, 1, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, shading_value));
	}

	/* Bind the vertex array and all buffers*/
	void Renderer::bindAll() const
	{
		vao.bind();
		vbo.bind();
		ibo.bind();
	}
	/* Draw the triangles */
	void Renderer::draw(unsigned int index_count) const
	{
		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
	}
}