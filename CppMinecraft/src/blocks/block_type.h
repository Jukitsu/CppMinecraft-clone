#pragma once

#include <string>

#include "renderer/geometry.h"
#include "models/models.h"
#include "texture/texture_manager.h"

namespace Blocks
{
	class BlockType
	{
		Models::Model* model;
		Geometry::Quad* quads;
		Texturing::TextureManager* texture_manager;
	public:
		const char* name;
		unsigned int id;
		BlockType(Texturing::TextureManager* texture_manager, const char* name,
			unsigned int id, Models::Model* model, const std::string& texture_filepath);
		BlockType(const BlockType& other);
		~BlockType() noexcept;

		const Geometry::Quad* get_quads() const;
		unsigned int get_quad_number() const;
	};
}