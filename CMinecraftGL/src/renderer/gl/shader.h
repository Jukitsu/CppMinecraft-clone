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
	std::string _parseShader(const std::string& filepath);
	const std::string shader_source;
public:
	GLuint id;
	Shader(const std::string& shader_file_path, GLuint type);
	void clear();
};

class ShaderProgram {
public:
	GLuint id;
	ShaderProgram();
	void bindShader(Shader shader);
	void compileProgram();
	void use();
	void stop();
	GLint find_uniform(const GLchar* name);
	void setUniform1f(const GLchar* name, GLfloat value);
	void setUniform4f(const GLchar* name, GLfloat i, GLfloat j, GLfloat k, GLfloat l);
	void setUniformMat4f(const GLchar* name, const glm::mat4& matrix);
	void delete_program();
};

ShaderProgram createShaderProgram(Shader vertexShader, Shader fragmentShader);