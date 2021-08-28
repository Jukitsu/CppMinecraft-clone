#pragma once

#include <array>
#include <queue>
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
		std::queue<std::shared_ptr<Chunk>> chunk_mesh_loading_queue;
	public:
		ChunkManager(std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types);
		ChunkManager(const ChunkManager& other) = delete;
		ChunkManager(ChunkManager&& rvalue) = delete;
		~ChunkManager() noexcept;
		void renderChunks();
		void updateChunkMeshQueue();
		void reloadChunkMesh();
	};
}