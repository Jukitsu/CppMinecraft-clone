#include <GL/glew.h>
#include <GL/glu.h>

GLuint compile_shader(GLuint type, const std::string& source);
GLuint create_shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
std::string ParseShader(const std::string& filepath);