#include "shader.h"

namespace AbstractGL
{
	GLuint Shader::_compileShader(GLuint type)
	{
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
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
				<< " shader\n";
			std::cout << message << "\n";
			delete[] message;
			glDeleteShader(_id);
			return 0;
		}

		return _id;
	}
	std::string Shader::_parseShader(const char* filepath)
	{
		std::ifstream stream(filepath);
		if (!stream) std::cerr << "Could not open the file!" << std::endl;
		std::string line;
		std::stringstream source;
		while (getline(stream, line)) {
			source << line << '\n';
		}
		return source.str();
	}

}