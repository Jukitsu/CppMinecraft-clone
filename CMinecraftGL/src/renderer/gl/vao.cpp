#include "vao.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>


VertexArray::VertexArray():id(){}


VertexArray::~VertexArray() {
	glCall (glDeleteVertexArrays(1, &id));
}

void VertexArray::init() {
	glCall (glGenVertexArrays(1, &id));
}

void VertexArray::bind() {
	glCall (glBindVertexArray(id));
}

void VertexArray::unbind() {
	glCall (glBindVertexArray(0));
}