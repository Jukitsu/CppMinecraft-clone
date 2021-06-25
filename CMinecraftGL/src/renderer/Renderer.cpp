#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "gl/vao.h"
#include "gl/vbo.h"
#include "gl/ibo.h"
#include "Renderer.h"

Renderer::Renderer() : vao(), vbos(), ibo(), is_bound(false), va_index(0) 
{
	vao = new VertexArray();
	for (int i = 0; i < 1; i++) {
		vbos[i] = new VertexBuffer();
	}
	ibo = new IndexBuffer();
}
// This constructor is just here to initialize random stuff
Renderer::~Renderer() {
	delete vao;
	for (VertexBuffer* vbo: vbos) {
		delete vbo;
	}
	delete ibo;
}
void Renderer::init() {
	vao->init();
	for (VertexBuffer* vbo: vbos) {
		vbo->init();
	}
	ibo->init();
	std::cout << vao->id << std::endl;
}

void Renderer::sendData(GLfloat* data, GLint data_size, GLint data_dim, GLuint* indices, GLint index_count, GLuint attr_index) {
	vao->bind();
	VertexBuffer* vbo = vbos[attr_index];
	vbo->sendData(data, data_size * sizeof(GLfloat), data_dim, attr_index);
	vbo->bind();
	ibo->sendIndices(indices, index_count * sizeof(GLuint));
	ibo->bind();
	std::cout << data << std::endl;
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
	glCall (glClear(GL_COLOR_BUFFER_BIT));
	glCall (glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	return 0;
}

