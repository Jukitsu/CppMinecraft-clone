#pragma once

#include <memory>
#include <vector>

#include "texture/texture_manager.h"
#include "abstractgl/shader.h"
#include "blocks/block_type.h"
#include "chunk/chunk_manager.h"
#include "chunk/chunk_math.h"

namespace World
{
	class World
	{
		Blocks::Models::BlockModels models;
		std::shared_ptr<Texturing::TextureManager> texture_manager;
		std::array<Blocks::BlockType*, BLOCK_COUNT> block_types;
	public:
		std::unique_ptr<ChunkManager> chunk_manager;
		World(const std::shared_ptr<Texturing::TextureManager>& texture_manager);
		~World() noexcept;
		void setBlock(const glm::vec3& pos, int block);
		void render()
		{
			chunk_manager->updateChunkMeshQueue();
			chunk_manager->renderChunks();
		}
	};
}