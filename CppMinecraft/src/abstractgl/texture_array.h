#pragma once
#include "OpenGL.h"

namespace AbstractGL
{
	class TextureArray
	{
		GLuint id;
		static const TextureArray* bound;
	public:
		TextureArray(GLsizei texture_width, GLsizei texture_height, GLsizei array_size, 
			bool do_mipmap, GLenum mipmap_type);
		~TextureArray() noexcept
		{
			glDeleteTextures(1, &id);
		}

		void addTextureData(GLsizei width, GLsizei height, int32_t index, GLubyte* data);

		void bind() const
		{
			if (bound != this)
			{
				glBindTexture(GL_TEXTURE_2D_ARRAY, id);
				bound = this;
			}
		}
		void activate() const
		{
			glActiveTexture(GL_TEXTURE0);
			bind();
		}
		void generateMipmaps() const
		{
			bind();
			glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		}
	};
}