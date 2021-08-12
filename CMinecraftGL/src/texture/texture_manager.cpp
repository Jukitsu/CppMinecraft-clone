#include "texture_manager.h"

TextureManager::TextureManager()
{}

TextureManager::TextureManager(GLsizei texture_width, GLsizei texture_height, ShaderProgram *program)
	:width(texture_width), height(texture_height), shader_program(program), texture_images(),
	sampler_location()
{
	glCall (glGenTextures(1, &id));
	glCall (glBindTexture(GL_TEXTURE_2D_ARRAY, id));
	glCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	glCall (glTexImage3D(
		GL_TEXTURE_2D_ARRAY, 0, GL_RGBA,
		width, height, 32,
		0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	sampler_location = shader_program->find_uniform("texture_array_sampler");
}



TextureManager::~TextureManager() {
	unbind();
	for (Image *image : texture_images)
		delete image;
	glCall (glDeleteTextures(1, &id));
}

void TextureManager::bind() const {
	glCall (glBindTexture(GL_TEXTURE_2D_ARRAY, id));
}

void TextureManager::unbind() const {
	glCall (glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
}

void TextureManager::add_texture(const std::string &texture_path, GLint index) {
	Image *texture_image = new Image;
	texture_image->image_data = stbi_load(texture_path.c_str(), 
		&texture_image->width, &texture_image->height,
		&texture_image->comp, 0);
	texture_images[index] = texture_image;
	bind();
	glCall (glTexSubImage3D(
		GL_TEXTURE_2D_ARRAY, 0,
		0, 0, index,
		width, height, 1,
		GL_RGBA, GL_UNSIGNED_BYTE,
		texture_image->image_data));
	stbi_image_free(texture_image->image_data);
}
 
void TextureManager::generate_mipmaps() const {
	bind();
	glCall (glGenerateMipmap(GL_TEXTURE_2D_ARRAY));
}

void TextureManager::activate() {
	glCall (glActiveTexture(GL_TEXTURE0));
	bind();
	shader_program->setUniform1i(sampler_location, 0);
}