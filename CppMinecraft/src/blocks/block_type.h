#pragma once

#include <vector>
#include <memory>

#include "renderer/geometry.h"
#include "models/models.h"
#include "texture/texture_manager.h"

typedef uint32_t BlockID;

namespace Blocks
{
	class BlockType
	{
		Models::Model* model;
		Geometry::Quad* quads;
		std::shared_ptr<Texturing::TextureManager> texture_manager;
	public:
		bool is_transparent;
		bool is_cube;
		const char* name;
		uint32_t id;
		BlockType(const char* name, size_t block_id, Models::Model* model,
			const std::vector<size_t>& texture_layout,
			bool is_transparent, bool is_cube);
		BlockType(const BlockType& other);
		~BlockType() noexcept;
		const Geometry::Quad* get_quads() const
		{
			return quads;
		}
		size_t get_quad_number() const
		{
			return model->get_quad_number();
		}
	};
}