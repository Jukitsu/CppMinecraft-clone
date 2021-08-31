#pragma once
#include <array>
#include <string>
#include "stb/stb_image.h"

#include "abstractgl/shader.h"
#include "abstractgl/texture_array.h"
#define TEX_ARRAY_SIZE 32

namespace Texturing
{
	struct Image
	{
		unsigned char* image_data;
		int width, height;
		int comp;
	};

	class TextureManager
	{
		AbstractGL::ShaderProgram* shader_program;
		Image texture_images[TEX_ARRAY_SIZE];
		AbstractGL::TextureArray texture_array;
		GLubyte sampler_location;
		mutable unsigned int current_index;
	public:
		TextureManager(unsigned int texture_width,
			unsigned int texture_height, AbstractGL::ShaderProgram* shader_program);
		~TextureManager();
		void addTexture(const std::string& texture_path);

		void generateMipmaps() const
		{
			texture_array.generateMipmaps();
		}
		void activate() const
		{
			texture_array.activate();
			shader_program->setUniform1i(sampler_location, 0); // Pass the Texture Array Sampler to the shaders
		}
		unsigned int getCurrentIndex() const
		{
			return current_index;
		}
	};
}