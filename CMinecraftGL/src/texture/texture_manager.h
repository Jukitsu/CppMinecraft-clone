#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/gl/glErrors.h"
#include "renderer/gl/shader.h"
#include "util/stb/stb_image.h"


struct Image {
	GLubyte *image_data;
	GLsizei width, height;
	GLint comp;
};

class TextureManager {
public:
	GLint sampler_location;
	ShaderProgram *shader_program;
	GLuint id;
	GLsizei width, height;
	Image *texture_images[32];
	TextureManager(GLsizei texture_width, GLsizei texture_height, ShaderProgram* program);
	~TextureManager();
	void bind();
	void unbind();
	void generate_mipmaps();
	void add_texture(const std::string &texture_path, GLint index);
	void activate();
};


