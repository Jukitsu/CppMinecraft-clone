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
	class Shader {
	private:
		GLuint _compileShader(GLuint type);
		std::string _parseShader(const char* filepath);
		std::string shader_source;
	public:
		GLuint id;
		Shader(const char* shader_file_path, GLuint type);
		~Shader() noexcept;
	};

	class ShaderProgram {
		GLuint id;
		const static ShaderProgram* used;
	public:
		ShaderProgram();
		~ShaderProgram() noexcept;
		void bindShader(Shader&& shader);
		void compile();
		void use() const;
		void stop() const;
		GLubyte findUniform(const GLchar* name);
		void setUniform1i(GLubyte location, GLint value);
		void setUniform4f(GLubyte location, GLfloat i, GLfloat j, GLfloat k, GLfloat l);
		void setUniformMat4f(GLubyte location, const glm::mat4& matrix);
	};
}

