#include "texture_manager.h"

namespace Texturing
{
	/* Manager for textures
	* It contains a array of image data structure and
	* on each add_texture call loads the image and parse it
	* in the OpenGL texture array
	*/
	using namespace AbstractGL;
	TextureManager::TextureManager(unsigned int texture_width,
		unsigned int texture_height, ShaderProgram* shader_program)
		:texture_array(texture_width, texture_height, TEX_ARRAY_SIZE),
		texture_images(), shader_program(shader_program)
	{
		/* Load the sampler location */
		sampler_location = shader_program->findUniform("texture_array_sampler");
	}

	TextureManager::~TextureManager()
	{
		
	}

	void TextureManager::addTexture(const std::string& texture_path, unsigned int index)
	{
		/* Load image data and parse it in the texture array*/
		Image* texture_image = texture_images + (index % TEX_ARRAY_SIZE); // Nasty C style pointer arithmetic >:)
		texture_image->image_data = stbi_load(texture_path.c_str(),
			&texture_image->width, &texture_image->height,
			&texture_image->comp, 0);
		texture_array.bind();
		texture_array.addTextureData(texture_image->width, texture_image->height, 
			index, texture_image->image_data);
		stbi_image_free(texture_image->image_data);
	}
	/* Pretty straightforward stuff */
	void TextureManager::generateMipmaps() const
	{
		texture_array.generateMipmaps();
	}
	void TextureManager::activate() const
	{
		texture_array.activate();
		shader_program->setUniform1i(sampler_location, 0); // Pass the Texture Array Sampler to the shaders
	}
}