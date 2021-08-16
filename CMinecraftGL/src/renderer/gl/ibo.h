#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "glErrors.h"



class IndexBuffer {
public:
	GLuint id;
	mutable bool is_bound;
	IndexBuffer();
	~IndexBuffer();
	void init();
	void bufferIndices(const void* indices, GLuint size);
	void bind() const;
	void unbind() const;
};

