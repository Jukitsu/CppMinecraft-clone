#pragma once

#include <map>
#include <memory>
#include <glm/vec3.hpp>

#include "chunk.h"


namespace World
{
	class ChunkManager
	{
		std::shared_ptr<std::vector<Blocks::BlockType>> block_types;
		std::vector<std::shared_ptr<Chunk>> chunks;
	public:
		ChunkManager(const std::shared_ptr<std::vector<Blocks::BlockType>>& block_types);
		~ChunkManager() noexcept;
		void renderChunks();
	};
}