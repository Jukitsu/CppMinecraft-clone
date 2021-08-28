#include "block_type.h"

namespace Blocks
{
	/*
	* Small Wrapper for Block models and attributes
	* The 3D array in chunks will use numeric IDs though
	* However to access these attributes there is a "block_type" array
	* created in the "World::World" class
	*/
	using Texturing::TextureManager;
	using namespace Geometry;
	using namespace Models;

	BlockType::BlockType(std::shared_ptr<TextureManager> texture_manager, const char* name,
		unsigned int id, Model* model, const std::string& texture_filepath,
		bool is_transparent, bool is_cube)
		:name(name), id(id), texture_manager(texture_manager), model(model),
		is_transparent(is_transparent), is_cube(is_cube)
	{
		/* Load the models and copy them (the copy is necessary though for textures) */
		if (model->get_quad_number())
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
		else
			quads = nullptr;
	}
	/* Copy constructor (I will try to avoid using them) */
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
	/* Encapsulation stuff */
	const Quad* BlockType::get_quads() const
	{
		return quads;
	}
	constexpr unsigned int BlockType::get_quad_number() const
	{
		return model->get_quad_number();
	}
}