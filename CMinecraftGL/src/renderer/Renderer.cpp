#include "Renderer.h"

Renderer::Renderer() : vao(), vbo(), ibo(), index_count(), is_bound(false)
{}
// This constructor is just here to initialize random stuff
Renderer::~Renderer() noexcept {}
void Renderer::init() {
	vao.init();
	vbo.init();
	ibo.init();
}

void Renderer::sendData(const Mesh &mesh)
{
	vao.bind();
	vbo.sendData(mesh.mesh_data.data(), mesh.mesh_data.size() * sizeof(GLfloat));
	ibo.sendIndices(mesh.mesh_indices.data(), mesh.mesh_indices.size() * sizeof(GLuint));
	index_count = mesh.mesh_indices.size();
}


void Renderer::link_attrib(GLubyte va_index, BufferLayout *layout)
{
	vao.link_attrib(&vbo, va_index, layout->dim, GL_FLOAT, layout->stride, layout->offset);
}


void Renderer::bind_all() const {
	is_bound = true;
	vao.bind();
	ibo.bind();
}

void Renderer::clear() const {
	is_bound = false;
	ibo.unbind();
	vbo.unbind();
	vao.unbind();
}

int Renderer::draw() {
	if (!is_bound) {
		std::cerr << "No vao is bound" << std::endl;
		return -1;
	}
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_SHORT, nullptr);
	return 0;
}

