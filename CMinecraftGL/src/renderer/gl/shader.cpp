#define GLEW_STATIC
#include <fstream>
#include <string>
#include <sstream>
#include <memory.h>
#include "shader.h"
#include "util/glm/glm.hpp"
#include "util/glm/gtc/type_ptr.hpp"


std::string Shader::_parseShader(const std::string &filepath) {
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
    const char *src = shader_source.c_str();
    glShaderSource(_id, 1, &src, nullptr);
    glCompileShader(_id);

    int result;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length];
        glGetShaderInfoLog(_id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader\n";
        std::cout << message << "\n";
        delete[] message;
        glDeleteShader(_id);
        return 0;
    }

    return _id;
}
Shader::Shader(const std::string &shader_file_path, GLuint type)
    :shader_source(_parseShader(shader_file_path)), id(_compileShader(type))
{}

Shader::Shader(Shader &&shader) noexcept
    :id(shader.id), shader_source(std::move(shader.shader_source))
{
    shader.id = 0;
}

Shader::~Shader() noexcept {
    glDeleteShader(id);
}

ShaderProgram::ShaderProgram() 
{
    id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() noexcept {
    stop();
    glDeleteProgram(id);
}

void ShaderProgram::bind_shader(Shader &&shader) {
	glAttachShader(id, shader.id);
}


void ShaderProgram::compile() {
	glLinkProgram(id);
	glValidateProgram(id);
}

void ShaderProgram::use() {
    glUseProgram(id);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}


GLubyte ShaderProgram::find_uniform(const GLchar *name) {
    return glGetUniformLocation(id, name);
}


void ShaderProgram::setUniform1i(GLubyte location, GLint value) {
    glUniform1i(location, value);
}

void ShaderProgram::setUniform4f(GLubyte location, GLfloat i, GLfloat j, GLfloat k, GLfloat l) {
    glUniform4f(location, i, j, k, l);
}

void ShaderProgram::setUniformMat4f(GLubyte location, const glm::mat4 &matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


