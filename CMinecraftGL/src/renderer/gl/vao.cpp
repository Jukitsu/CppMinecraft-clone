#include "vao.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

VertexArray::~VertexArray() {
	glDeleteBuffers(1, &id);
}

void VertexArray::bind() {
	glBindVertexArray(id);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}