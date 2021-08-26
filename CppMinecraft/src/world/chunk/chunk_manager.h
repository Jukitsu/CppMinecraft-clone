#pragma once

#include <array>
#include <memory>
#include <glm/vec3.hpp>

#include "chunk.h"


namespace World
{
	class ChunkManager
	{
		unsigned long max_chunk_index_count;
		unsigned int* chunk_indices;
		std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types;
		std::vector<std::shared_ptr<Chunk>> chunks;
	public:
		ChunkManager(std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types);
		ChunkManager(const ChunkManager& other) = delete;
		ChunkManager(ChunkManager&& rvalue) = delete;
		~ChunkManager() noexcept;
		void renderChunks();
	};
}