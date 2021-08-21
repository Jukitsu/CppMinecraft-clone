#include "texture_manager.h"

namespace Texturing
{
	using namespace AbstractGL;
	TextureManager::TextureManager(unsigned int texture_width,
		unsigned int texture_height, ShaderProgram* shader_program)
		:texture_array(texture_width, texture_height, TEX_ARRAY_SIZE),
		texture_images(), shader_program(shader_program)
	{
		sampler_location = shader_program->findUniform("texture_array_sampler");
	}

	TextureManager::~TextureManager()
	{
		
	}

	void TextureManager::addTexture(const std::string& texture_path, unsigned int index)
	{
		Image* texture_image = texture_images + (index % TEX_ARRAY_SIZE);
		texture_image->image_data = stbi_load(texture_path.c_str(),
			&texture_image->width, &texture_image->height,
			&texture_image->comp, 0);
		texture_array.bind();
		texture_array.addTextureData(texture_image->width, texture_image->height, 
			index, texture_image->image_data);
		stbi_image_free(texture_image->image_data);
	}
	void TextureManager::generateMipmaps() const
	{
		texture_array.generateMipmaps();
	}
	void TextureManager::activate() const
	{
		texture_array.activate();
		shader_program->setUniform1i(sampler_location, 0);
	}
}