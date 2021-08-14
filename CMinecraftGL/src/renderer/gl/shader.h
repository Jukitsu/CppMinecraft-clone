#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <util/glm/glm.hpp>
#include "glErrors.h"

class Shader {
private:
	GLuint _compileShader(GLuint type);
	std::string _parseShader(const std::string &filepath);
	std::string shader_source;
public:
	GLuint id;
	Shader(Shader &&shader) noexcept;
	Shader(const std::string &shader_file_path, GLuint type);
	~Shader() noexcept;
};

class ShaderProgram {
public:
	GLubyte id;
	ShaderProgram();
	~ShaderProgram() noexcept;
	void bind_shader(Shader &&shader);
	void compile();
	void use();
	void stop();
	GLubyte find_uniform(const GLchar *name);
	void setUniform1i(GLubyte location, GLint value);
	void setUniform4f(GLubyte location, GLfloat i, GLfloat j, GLfloat k, GLfloat l);
	void setUniformMat4f(GLubyte location, const glm::mat4 &matrix);
};

