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
	const std::string shader_source;
public:
	GLuint id;
	Shader(const std::string &shader_file_path, GLuint type);
	~Shader();
};

class ShaderProgram {
public:
	GLuint id;
	ShaderProgram();
	~ShaderProgram();
	void bind_shader(Shader shader);
	void compile();
	void use();
	void stop();
	GLint find_uniform(const GLchar *name);
	void setUniform1i(GLint location, GLint value);
	void setUniform4f(GLint location, GLfloat i, GLfloat j, GLfloat k, GLfloat l);
	void setUniformMat4f(GLint location, const glm::mat4 &matrix);
};

