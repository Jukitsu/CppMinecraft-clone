#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class VertexBuffer {
private:
	GLuint id;
	GLuint attr_pointer;
public:
	VertexBuffer(const void* data, GLuint size);
	~VertexBuffer();
	void bind();
	void unbind();
	void genVertexAttrib(GLuint va_pointer, GLint pointer_size);
};

