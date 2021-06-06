#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "shader.h" 


GLuint compile_shader(unsigned int type, const std::string& source) {
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" <<
            std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

GLuint create_shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    GLuint program = glCreateProgram();
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

std::string ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream source;
    while (getline(stream, line)) {
        source << line << '\n';
    }
    return source.str();
}

