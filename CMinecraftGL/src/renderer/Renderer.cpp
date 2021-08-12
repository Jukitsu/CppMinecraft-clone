#include "Renderer.h"

Renderer::Renderer() : vao(), vbo(), ibo(), index_count(), is_bound(false)
{}
// This constructor is just here to initialize random stuff
Renderer::~Renderer() {}
void Renderer::init() {
	vao.init();
	vbo.init();
	ibo.init();
}

void Renderer::sendData(const GLfloat *data, GLint data_size, GLint data_dim, const GLuint *indices, GLint index_count, GLuint va_index) {
	this->index_count = index_count;
	vao.bind();
	vbo.sendData(data, data_size * sizeof(GLfloat));
	ibo.bind();
	ibo.sendIndices(indices, index_count * sizeof(GLuint));
}

void Renderer::link_attrib(GLuint va_index, GLint data_dim, GLenum type, GLsizei stride, int offset) {
	vao.link_attrib(&vbo, va_index, data_dim, type, stride, offset);
}

void Renderer::bind_all() {
	is_bound = true;
	vao.bind();
	ibo.bind();
}

void Renderer::clear() {
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
	glCall (glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr));
	return 0;
}

