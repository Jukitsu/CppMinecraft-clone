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
	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ibo;
	int index_count;
	bool is_bound;
public:
	Renderer();
	~Renderer();
	void init();
	void sendData(const GLfloat *data, GLint data_size, GLint data_dim, const GLuint *indices, GLint index_count, GLuint va_index);
	void bind_all();
	void link_attrib(GLuint va_index, GLint data_dim, GLenum type, GLsizei stride, int offset);
	void clear();
	int draw();
};