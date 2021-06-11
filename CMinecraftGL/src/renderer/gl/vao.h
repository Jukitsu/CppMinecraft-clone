#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>



class VertexArray {
public:
	GLuint id;
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
};



