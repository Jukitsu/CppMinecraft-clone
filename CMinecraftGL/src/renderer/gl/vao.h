#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class VertexArray {
private:
	GLuint id;
public:
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
};



