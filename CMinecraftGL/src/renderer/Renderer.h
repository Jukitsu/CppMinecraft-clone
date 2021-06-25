#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include "gl/vao.h"
#include "gl/vbo.h"
#include "gl/ibo.h"
#include <GLFW/glfw3.h>
#include "gl/glErrors.h"



class Renderer {
private:
	VertexArray* vao;
	VertexBuffer* vbos[1];
	IndexBuffer* ibo;
	GLuint va_index;
	bool is_bound;
public:
	Renderer();
	~Renderer();
	void init();
	void sendData(GLfloat* data, GLint data_size, GLint data_dim, GLuint* indices, GLint index_count, GLuint attr_index);
	void bind_all();
	void clear();
	int draw();
};