#include "Renderer.h"


/*------------Some kind of renderer API------------*/
Renderer::Renderer() : vao(), vbo(), ibo(), index_count(), is_bound(false)
{}
// This constructor is just here to initialize random stuff
Renderer::~Renderer() noexcept {}
inline void Renderer::init() {
	vao.init();
	vbo.init();
	ibo.init();
}


inline void Renderer::bufferData(const Mesh &mesh)
{
	vao.bind();
	vbo.bufferData(mesh.vertices.data(), mesh.current_vertex_data_size * sizeof(GLfloat));
	ibo.bufferIndices(mesh.indices.data(), mesh.index_count * sizeof(GLushort));
	index_count = mesh.index_count;
}

inline void Renderer::bind_layout()
{
	vao.link_attrib(&vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
	vao.link_attrib(&vbo, 1, 3, GL_BYTE, sizeof(Vertex), offsetof(Vertex, tex_coords));
	vao.link_attrib(&vbo, 2, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), offsetof(Vertex, shading_value));
}


inline void Renderer::bind_all() const {
	is_bound = true;
	vao.bind();
	ibo.bind();
}

inline void Renderer::clear() const {
	is_bound = false;
	ibo.unbind();
	vbo.unbind();
	vao.unbind();
}

inline void Renderer::draw() const {
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_SHORT, nullptr);
}

