#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "shader.h"

std::string Shader::_parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    if (!stream) std::cerr << "Could not open the file!" << std::endl;
    std::string line;
    std::stringstream source;
    while (getline(stream, line)) {
        source << line << '\n';
    }
    return source.str();
}

GLuint Shader::_compileShader(GLuint type) {
    GLuint _id = glCreateShader(type);
    const char* src = shader_source.c_str();
    glShaderSource(_id, 1, &src, nullptr);
    glCompileShader(_id);

    int result;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(_id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" <<
            std::endl;
        std::cout << message << std::endl;
        glDeleteShader(_id);
        return 0;
    }

    return _id;
}
Shader::Shader(const std::string& shader_file_path, GLuint type)
    :shader_source(_parseShader(shader_file_path)), id(_compileShader(type))
{

}

void Shader::clear() {
    glDeleteShader(id);
}

ShaderProgram::ShaderProgram() 
{
    id = glCreateProgram();
}

void ShaderProgram::bindShader(Shader shader) {
	glAttachShader(id, shader.id);
}

void ShaderProgram::compileProgram() {
	glLinkProgram(id);
	glValidateProgram(id);
}

void ShaderProgram::use() {
    glUseProgram(id);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

ShaderProgram createShaderProgram(Shader vertexShader, Shader fragmentShader) {
    ShaderProgram program = ShaderProgram();
    program.bindShader(vertexShader);
    program.bindShader(fragmentShader);
    program.compileProgram();
    return program;
}