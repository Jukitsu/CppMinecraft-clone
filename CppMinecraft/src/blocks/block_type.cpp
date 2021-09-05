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
	
	BlockType::BlockType(const char* name, size_t block_id, Models::Model* model,
		const std::vector<size_t>& texture_layout,
		bool is_transparent, bool is_cube)
		:name(name), id(block_id), texture_manager(texture_manager), model(model),
		is_transparent(is_transparent), is_cube(is_cube)
	{
		/* Load the models and copy them (the copy is necessary though for textures) */
		if (model->get_quad_number())
		{
			quads = new Quad[model->get_quad_number()];
			memcpy(quads, model->get_quads(), model->get_quad_number() * sizeof(Quad));
			
			for (uint8_t i = 0; i < model->get_quad_number(); i++)
			{
				for (Vertex& vertex : quads[i].vertices)
				{
					vertex.tex_index = texture_layout[i];
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
}