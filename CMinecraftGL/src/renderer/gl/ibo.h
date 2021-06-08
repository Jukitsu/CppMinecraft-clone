#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class IndexBuffer {
private:
	GLuint id;
public:
	IndexBuffer(const void* indices, GLuint size);
	~IndexBuffer();
	void bind();
	void unbind();
};

