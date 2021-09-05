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
		size_t getVBOsize()
		{
			return vbo.current_size;
		}
		/* Allocate the Vertex Buffer and pass the Indices */
		void allocateBuffers(size_t max_vertex_count, size_t max_index_count,
			uint32_t* indices)
		{
			vao.bind();
			vbo.allocate(max_vertex_count * sizeof(Geometry::Vertex));
			ibo.bufferData(indices,
				max_index_count * sizeof(GLuint));
		}
		void reallocVBO(size_t new_capacity)
		{
			vbo.allocate(new_capacity * sizeof(Geometry::Vertex));
		}
		/* Push the batched data to the Vertex Buffer */
		void bufferBatch(const Mesh& mesh, ptrdiff_t offset)
		{
			vao.bind();
			vbo.bufferSubData(mesh.getVertexData().data(),
				mesh.getVertexData().size() * sizeof(Geometry::Vertex),
				offset * sizeof(Geometry::Vertex));
		}
		/* Bind the Vertex Attributes to the VAOs with the specified layout:
		* posX, posY, posZ, texX, texY, texZ, shading_value
		*/
		void bindLayout()
		{
			vao.linkAttrib(&vbo, 0, 3, 
				GL_FLOAT, sizeof(Geometry::Vertex), 
				offsetof(Geometry::Vertex, position));
			vao.linkAttrib(&vbo, 1, 2, 
				GL_UNSIGNED_INT, sizeof(Geometry::Vertex),
				offsetof(Geometry::Vertex, tex_UV));
			vao.linkAttrib(&vbo, 2, 2,
				GL_UNSIGNED_INT, sizeof(Geometry::Vertex),
				offsetof(Geometry::Vertex, tex_index));
			vao.linkAttrib(&vbo, 3, 1, 
				GL_FLOAT, sizeof(Geometry::Vertex),
				offsetof(Geometry::Vertex, shading_value));
		}

		/* Bind the vertex array and all buffers*/
		void bindAll() const
		{
			vao.bind();
			vbo.bind();
			ibo.bind();
		}
		/* Draw the triangles */
		void draw(uint32_t index_count) const
		{
			vao.bind();
			ibo.bind();
			glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
		}
	};
}