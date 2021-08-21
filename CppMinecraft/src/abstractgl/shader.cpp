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
	Shader::Shader(const char* shader_file_path, GLuint type)
		:shader_source(_parseShader(shader_file_path)), id(_compileShader(type))
	{

	}
	Shader::~Shader() noexcept
	{
		glDeleteShader(id);
	}


	const ShaderProgram* ShaderProgram::used = nullptr;

	ShaderProgram::ShaderProgram()
	{
		id = glCreateProgram();
	}
	ShaderProgram::~ShaderProgram() noexcept
	{
		stop();
		glDeleteProgram(id);
	}

	void ShaderProgram::bindShader(Shader&& shader)
	{
		glAttachShader(id, shader.id);
	}
	void ShaderProgram::compile()
	{
		glLinkProgram(id);
		glValidateProgram(id);
	}
	void ShaderProgram::use() const
	{
		if (used != this)
		{
			glUseProgram(id);
			used = this;
		}
	}
	void ShaderProgram::stop() const
	{
		if (used == this)
		{
			glUseProgram(0);
			used = nullptr;
		}
	}

	GLubyte ShaderProgram::findUniform(const GLchar* name)
	{
		return glGetUniformLocation(id, name);
	}
	void ShaderProgram::setUniform1i(GLubyte location, GLint value)
	{
		glUniform1i(location, value);
	}
	void ShaderProgram::setUniform4f(GLubyte location, GLfloat i, GLfloat j, GLfloat k, GLfloat l)
	{
		glUniform4f(location, i, j, k, l);
	}
	void ShaderProgram::setUniformMat4f(GLubyte location, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}