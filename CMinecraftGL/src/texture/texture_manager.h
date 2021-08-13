#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/gl/glErrors.h"
#include "renderer/gl/shader.h"
#include "util/stb/stb_image.h"
#define TEX_ARRAY_SIZE 32

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
	Image texture_images[TEX_ARRAY_SIZE];
	TextureManager();
	TextureManager(GLsizei texture_width, GLsizei texture_height, ShaderProgram *program);
	~TextureManager() noexcept;
	void bind() const;
	void unbind() const;
	void generate_mipmaps() const;
	void add_texture(const std::string &texture_path, GLint index);
	void activate();
};


