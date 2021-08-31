#pragma once

#include <abstractgl/shader.h>
#include <abstractgl/buffers.h>
#include <abstractgl/vertex_array.h>

#include "mesh.h"

namespace Rendering
{
	class Renderer
	{
		/* Wrapper for the Chunk Renderers
		* Holds the VAO, VBO and IBOs and a
		* pointer to the shaders
		* Use Batch Rendering and Abstracted OpenGL API
		* to make things easier
		*/
		AbstractGL::VertexArray vao;
		AbstractGL::VertexBuffer vbo;
		AbstractGL::IndexBuffer ibo;
		AbstractGL::ShaderProgram* shader_program;
	public:
		Renderer()
			:vao(), vbo(), ibo(), shader_program()
		{

		}

		~Renderer() noexcept
		{

		}
		/* Allocate the Vertex Buffer and pass the Indices */
		void allocateBuffers(const Mesh& mesh)
		{
			vao.bind();
			ibo.bufferData(mesh.getIndices(),
				mesh.getMaxIndexCount() * sizeof(unsigned int));
		}
		/* Push the batched data to the Vertex Buffer */
		void bufferBatch(const Mesh& mesh)
		{
			vao.bind();
			vbo.bufferData(mesh.getVertexData().data(),
				mesh.getVertexData().size() * sizeof(Geometry::Vertex));
		}
		/* Bind the Vertex Attributes to the VAOs with the specified layout:
		* posX, posY, posZ, texX, texY, texZ, shading_value
		*/
		void bindLayout()
		{
			vao.linkAttrib(&vbo, 0, 3, GL_FLOAT, sizeof(Geometry::Vertex), offsetof(Geometry::Vertex, position));
			vao.linkAttrib(&vbo, 1, 3, GL_FLOAT, sizeof(Geometry::Vertex), offsetof(Geometry::Vertex, tex_coords));
			vao.linkAttrib(&vbo, 2, 1, GL_FLOAT, sizeof(Geometry::Vertex), offsetof(Geometry::Vertex, shading_value));
		}

		/* Bind the vertex array and all buffers*/
		void bindAll() const
		{
			vao.bind();
			vbo.bind();
			ibo.bind();
		}
		/* Draw the triangles */
		void draw(unsigned int index_count) const
		{
			vao.bind();
			ibo.bind();
			glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
		}
	};
}