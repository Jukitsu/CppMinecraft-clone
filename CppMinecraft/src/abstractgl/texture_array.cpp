#include "texture_array.h"

namespace AbstractGL
{
	TextureArray::TextureArray(GLsizei texture_width, GLsizei texture_height, GLsizei array_size)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D_ARRAY, id);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage3D(
			GL_TEXTURE_2D_ARRAY, 0, GL_RGBA,
			texture_width, texture_height, array_size,
			0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	}
	

	void TextureArray::addTextureData(GLsizei width, 
		GLsizei height, int index, GLubyte* data)
	{
		bind();
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY, 0,
			0, 0, index,
			width, height, 1,
			GL_RGBA, GL_UNSIGNED_BYTE,
			data);
	}
	
}