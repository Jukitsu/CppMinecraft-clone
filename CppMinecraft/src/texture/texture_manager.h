#pragma once
#include <array>
#include <string>
#include "stb/stb_image.h"

#include "abstractgl/shader.h"
#include "abstractgl/texture_array.h"


namespace Texturing
{
	constexpr uint32_t TEX_ARRAY_SIZE = 32;
	struct Image
	{
		GLubyte* image_data;
		GLsizei width, height;
		GLint comp;
	};

	class TextureManager
	{
		AbstractGL::ShaderProgram* shader_program;
		Image texture_images[TEX_ARRAY_SIZE];
		AbstractGL::TextureArray texture_array;
		GLubyte sampler_location;
		mutable uint32_t current_index;
	public:
		TextureManager(size_t texture_width,
			size_t texture_height, AbstractGL::ShaderProgram* shader_program);
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
		uint32_t getCurrentIndex() const
		{
			return current_index;
		}
	};
}