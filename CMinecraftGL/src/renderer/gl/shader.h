#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shader {
private:
	GLuint _compileShader(GLuint type);
	std::string _parseShader(const std::string& filepath);
	const std::string& shader_source;
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
	void delete_program();
};

ShaderProgram createShaderProgram(Shader vertexShader, Shader fragmentShader);