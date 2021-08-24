#pragma once

#include <string>
#include <memory>

#include "renderer/geometry.h"
#include "models/models.h"
#include "texture/texture_manager.h"

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
		unsigned int id;
		BlockType(std::shared_ptr<Texturing::TextureManager> texture_manager, const char* name,
			unsigned int id, Models::Model* model, const std::string& texture_filepath,
			bool is_transparent, bool is_cube);
		BlockType(const BlockType& other);
		~BlockType() noexcept;
		const Geometry::Quad* get_quads() const;
		constexpr unsigned int get_quad_number() const;
	};
}