#define GLEW_STATIC
#include <fstream>
#include <string>
#include <sstream>
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
    const char* src = shader_source.c_str();
    glCall (glShaderSource(_id, 1, &src, nullptr));
    glCall (glCompileShader(_id));

    int result;
    glCall (glGetShaderiv(_id, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        glCall (glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length));
        char* message = new char[length];
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
{

}

void Shader::clear() {
    glCall (glDeleteShader(id));
}

ShaderProgram::ShaderProgram() 
{
    glCall (id = glCreateProgram());
}

void ShaderProgram::bindShader(Shader shader) {
	glCall (glAttachShader(id, shader.id));
}

void ShaderProgram::compileProgram() {
	glCall (glLinkProgram(id));
	glCall (glValidateProgram(id));
}

void ShaderProgram::use() {
    glCall (glUseProgram(id));
}

void ShaderProgram::stop() {
    glCall (glUseProgram(0));
}

void ShaderProgram::delete_program() {
    glCall (glDeleteProgram(id));
}

GLint ShaderProgram::find_uniform(const GLchar *name) {
    glCall (GLint location = glGetUniformLocation(id, name));
    return location;
}

void ShaderProgram::setUniform1f(const GLchar *name, GLfloat value) {
    GLint location = this->find_uniform(name);
    glCall (glUniform1f(location, value));
}

void ShaderProgram::setUniform4f(const GLchar *name, GLfloat i, GLfloat j, GLfloat k, GLfloat l) {
    GLint location = this->find_uniform(name);
    glCall (glUniform4f(location, i, j, k, l));
}

void ShaderProgram::setUniformMat4f(const GLchar *name, const glm::mat4 &matrix) {
    GLint location = this->find_uniform(name);
    glCall (glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}

ShaderProgram createShaderProgram(Shader vertexShader, Shader fragmentShader) {
    ShaderProgram program = ShaderProgram();
    program.bindShader(vertexShader);
    program.bindShader(fragmentShader);
    program.compileProgram();
    return program;
}