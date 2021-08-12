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
    glCall (glShaderSource(_id, 1, &src, nullptr));
    glCall (glCompileShader(_id));

    int result;
    glCall (glGetShaderiv(_id, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        glCall (glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length));
        char *message = new char[length];
        glCall (glGetShaderInfoLog(_id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" <<
            std::endl;
        std::cout << message << std::endl;
        delete[] message;
        glCall (glDeleteShader(_id));
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

Shader::~Shader() {
    glCall (glDeleteShader(id));
}

ShaderProgram::ShaderProgram() 
{
    glCall (id = glCreateProgram());
}

ShaderProgram::~ShaderProgram() {
    stop();
    glCall (glDeleteProgram(id));
}

void ShaderProgram::bind_shader(Shader &&shader) {
	glCall (glAttachShader(id, shader.id));
}


void ShaderProgram::compile() {
	glCall (glLinkProgram(id));
	glCall (glValidateProgram(id));
}

void ShaderProgram::use() {
    glCall (glUseProgram(id));
}

void ShaderProgram::stop() {
    glCall (glUseProgram(0));
}


GLint ShaderProgram::find_uniform(const GLchar *name) {
    glCall (GLint location = glGetUniformLocation(id, name));
    return location;
}


void ShaderProgram::setUniform1i(GLint location, GLint value) {
    glCall (glUniform1i(location, value));
}

void ShaderProgram::setUniform4f(GLint location, GLfloat i, GLfloat j, GLfloat k, GLfloat l) {
    glCall (glUniform4f(location, i, j, k, l));
}

void ShaderProgram::setUniformMat4f(GLint location, const glm::mat4 &matrix) {
    glCall (glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}


