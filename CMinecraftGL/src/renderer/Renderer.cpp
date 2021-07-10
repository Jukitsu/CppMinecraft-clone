#include "Renderer.h"

Renderer::Renderer() : vao(), vbos(), ibo(), index_count(), is_bound(false)
{
	vao = new VertexArray();
	for (int i = 0; i < 2; i++) {
		vbos[i] = new VertexBuffer();
	}
	ibo = new IndexBuffer();
}
// This constructor is just here to initialize random stuff
Renderer::~Renderer() {
	delete vao;
	for (VertexBuffer *vbo: vbos) {
		delete vbo;
	}
	delete ibo;
}
void Renderer::init() {
	vao->init();
	for (VertexBuffer *vbo: vbos) {
		vbo->init();
	}
	ibo->init();
}

void Renderer::sendData(GLfloat *data, GLint data_size, GLint data_dim, GLuint *indices, GLint index_count, GLuint va_index) {
	this->index_count = index_count;
	vao->bind();
	VertexBuffer *vbo = vbos[va_index];
	vbo->sendData(data, data_size * sizeof(GLfloat));
	vbo->bind();
	vao->link_attrib(vbo, data_dim, va_index);
	ibo->sendIndices(indices, index_count * sizeof(GLuint));
	ibo->bind();
}

void Renderer::bind_all() {
	is_bound = true;
	vao->bind();
	ibo->bind();
}

void Renderer::clear() {
	is_bound = false;
	glCall (glBindVertexArray(0));
	glCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

int Renderer::draw() {
	if (!is_bound) {
		std::cerr << "No vao is bound" << std::endl;
		return -1;
	}
	glCall (glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, nullptr));
	return 0;
}

