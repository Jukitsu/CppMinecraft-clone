#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include "gl/vao.h"
#include "gl/vbo.h"
#include "gl/ibo.h"
#include <GLFW/glfw3.h>
#include "gl/glErrors.h"
#include "Mesh.h"




class Renderer {
private:
	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ibo;
	size_t index_count;
	mutable bool is_bound;
public:
	Renderer();
	~Renderer() noexcept;
	void init();
	void bufferData(const Mesh &mesh);
	void bind_all() const;
	void bind_layout();
	void clear() const;
	void draw() const;
};