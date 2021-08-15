#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "models/models.h"
#include "texture/texture_manager.h"
#include "renderer/gl/geometry.h"


class Block
{
public:
	Model *model;
	Quad *quads;
	TextureManager *texture_manager;
	const char *name;
	unsigned int id;
	Block(TextureManager *texture_manager, const char *name, 
		unsigned int id, Model *model, const std::string &texture_filepath)
		:name(name), id(id), texture_manager(texture_manager), model(model)
	{
		quads = new Quad[model->get_quad_number()];
		memcpy(quads, model->get_quads(), model->get_quad_number() * sizeof(Quad));
		texture_manager->add_texture(texture_filepath, id);
		for (unsigned char i = 0; i < model->get_quad_number(); i++)
		{
			for (Vertex &vertex : quads[i].vertices)
			{
				vertex.tex_index = id;
			}
		}
	}

	~Block() noexcept
	{
		delete[] quads;
	}

};

