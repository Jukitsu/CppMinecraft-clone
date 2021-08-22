#pragma once

#include <memory>
#include <vector>

#include "texture/texture_manager.h"
#include "abstractgl/shader.h"
#include "blocks/block_type.h"
#include "chunk/chunk_manager.h"

namespace World
{
	class World
	{
		Blocks::Models::BlockModels models;
		std::shared_ptr<Texturing::TextureManager> texture_manager;
		std::shared_ptr<std::vector<Blocks::BlockType>> block_types;
		std::unique_ptr<ChunkManager> chunk_manager;
	public:
		World(const std::shared_ptr<Texturing::TextureManager>& texture_manager);
		~World() noexcept;

		void render();
	};
}