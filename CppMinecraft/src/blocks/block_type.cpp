#include "block_type.h"

namespace Blocks
{
	using Texturing::TextureManager;
	using namespace Geometry;
	using namespace Models;

	BlockType::BlockType(TextureManager* texture_manager, const char* name,
		unsigned int id, Model* model, const std::string& texture_filepath)
		:name(name), id(id), texture_manager(texture_manager), model(model)
	{
		quads = new Quad[model->get_quad_number()];
		memcpy(quads, model->get_quads(), model->get_quad_number() * sizeof(Quad));
		float tex_id = id; // Temporary
		texture_manager->addTexture(texture_filepath, tex_id);
		for (unsigned char i = 0; i < model->get_quad_number(); i++)
		{
			for (Vertex& vertex : quads[i].vertices)
			{
				vertex.tex_index = tex_id;
			}
		}
	}
	BlockType::BlockType(const BlockType& other)
		:name(other.name), id(other.id), texture_manager(other.texture_manager), model(other.model)
	{
		quads = new Quad[other.get_quad_number()];
		memcpy(quads, other.get_quads(), other.get_quad_number() * sizeof(Quad));
	}
	BlockType::~BlockType() noexcept
	{
		delete[] quads;
	}

	const Quad* BlockType::get_quads() const
	{
		return quads;
	}
	unsigned int BlockType::get_quad_number() const
	{
		return model->get_quad_number();
	}
}