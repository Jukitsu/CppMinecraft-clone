#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "gl/vao.h"
#include "gl/vbo.h"
#include "gl/ibo.h"
#include "Renderer.h"

Renderer::Renderer(): vaoptr(nullptr), vboptr(nullptr), iboptr(nullptr), is_bound(false), va_index(0) {}  
// This constructor is just here to initialize random stuff

void Renderer::genVertexArray() {
	VertexArray vao;
	vao.bind();
	vaoptr = &vao;
}

void Renderer::sendData(const void* data, const void* indices, GLuint sizeofdata, GLuint sizeofindices) {
	VertexBuffer vbo(data, sizeofdata, 3, va_index);
	IndexBuffer ibo(indices, sizeofindices);
	vbo.bind();
	ibo.bind();
	vboptr = &vbo; iboptr = &ibo;
}

void Renderer::bind_all() {
	is_bound = true;
	VertexArray vao = *vaoptr;
	IndexBuffer ibo = *iboptr;
	vao.bind();
	ibo.bind();
}

void Renderer::clear() {
	is_bound = false;
	vaoptr->unbind();
	vboptr->unbind();
	iboptr->unbind();
}

int Renderer::draw() {
	if (!is_bound) {
		std::cerr << "No vao is bound" << std::endl;
		return -1;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	return 0;
}

