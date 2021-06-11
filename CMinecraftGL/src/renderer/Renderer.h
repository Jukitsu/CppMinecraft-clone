#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "gl/vao.h"
#include "gl/vbo.h"
#include "gl/ibo.h"


class Renderer {
private:
	VertexArray* vaoptr;
	VertexBuffer* vboptr;
	IndexBuffer* iboptr;
	GLuint va_index;
	bool is_bound;
public:
	Renderer();
	void genVertexArray();
	void sendData(const void* data, const void* indices, GLuint sizeofdata, GLuint sizeofindices);
	void bind_all();
	void clear();
	int draw();
};