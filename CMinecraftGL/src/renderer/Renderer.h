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
	size_t index_count;
	mutable bool is_bound;
public:
	Renderer();
	~Renderer();
	void init();
	void sendData(const GLfloat *data, size_t data_size,
		const GLuint *indices, size_t index_count);
	void bind_all() const;
	void link_attrib(GLuint va_index, unsigned short data_dim, 
		GLenum type, GLsizei stride, int offset);
	void clear();
	int draw();
};