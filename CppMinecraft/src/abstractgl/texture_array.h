#pragma once
#include "OpenGL.h"

namespace AbstractGL
{
	class TextureArray
	{
		GLuint id;
		const static TextureArray* bound;
	public:
		TextureArray(GLsizei texture_width, GLsizei texture_height, GLsizei array_size);
		~TextureArray() noexcept;

		void addTextureData(GLsizei width, GLsizei height, int index, GLubyte* data);
		void bind() const;
		void activate() const;
		void generateMipmaps() const;
	};
}