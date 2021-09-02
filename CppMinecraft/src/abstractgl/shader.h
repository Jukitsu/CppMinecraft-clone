#pragma once
#include "OpenGL.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace AbstractGL
{
	class Shader 
	{
	private:
		GLuint _compileShader(GLuint type);
		std::string _parseShader(const char* filepath);
		std::string shader_source;
	public:
		GLuint id;
		Shader(const char* shader_file_path, GLuint type)
		{
			shader_source = _parseShader(shader_file_path);
			id = _compileShader(type);
		}
		~Shader() noexcept
		{
			glDeleteShader(id);
		}
	};

	class ShaderProgram 
	{
		GLuint id;
		const static ShaderProgram* used;
	public:
		ShaderProgram() 
		{
			id = glCreateProgram();
		}
		~ShaderProgram() noexcept 
		{
			stop();
			glDeleteProgram(id);
		}
		void bindShader(Shader&& shader)
		{
			glAttachShader(id, shader.id);
		}
		void compile()
		{
			glLinkProgram(id);
			glValidateProgram(id);
		}
		void use() const
		{
			if (used != this)
			{
				glUseProgram(id);
				used = this;
			}
		}
		void stop() const
		{
			if (used == this)
			{
				glUseProgram(0);
				used = nullptr;
			}
		}
		GLubyte findUniform(const GLchar* name)
		{
			return glGetUniformLocation(id, name);
		}
		void setUniform1i(GLubyte location, GLint value)
		{
			glUniform1i(location, value);
		}
		void setUniform4f(GLubyte location, GLfloat i, GLfloat j, GLfloat k, GLfloat l)
		{
			glUniform4f(location, i, j, k, l);
		}
		void setUniformMat4f(GLubyte location, const glm::mat4& matrix)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}
	};
}

