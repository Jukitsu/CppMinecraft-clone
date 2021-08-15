#include "texture_manager.h"

TextureManager::TextureManager()
{}

TextureManager::TextureManager(GLsizei texture_width, GLsizei texture_height, ShaderProgram *program)
	:width(texture_width), height(texture_height), shader_program(program), texture_images(),
	sampler_location()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage3D(
		GL_TEXTURE_2D_ARRAY, 0, GL_RGBA,
		width, height, 32,
		0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	sampler_location = shader_program->find_uniform("texture_array_sampler");
}



TextureManager::~TextureManager() noexcept {
	unbind();
	glDeleteTextures(1, &id);
}

void TextureManager::bind() const {
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
}

void TextureManager::unbind() const {
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureManager::add_texture(const std::string &texture_path, GLint index) {
	Image *texture_image = texture_images + (index % TEX_ARRAY_SIZE);
	texture_image->image_data = stbi_load(texture_path.c_str(), 
		&texture_image->width, &texture_image->height,
		&texture_image->comp, 0);
	bind();
	glTexSubImage3D(
		GL_TEXTURE_2D_ARRAY, 0,
		0, 0, index,
		width, height, 1,
		GL_RGBA, GL_UNSIGNED_BYTE,
		texture_image->image_data);
	stbi_image_free(texture_image->image_data);
}

void TextureManager::generate_mipmaps() const {
	bind();
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

void TextureManager::activate() {
	glActiveTexture(GL_TEXTURE0);
	bind();
	shader_program->setUniform1i(sampler_location, 0);
}