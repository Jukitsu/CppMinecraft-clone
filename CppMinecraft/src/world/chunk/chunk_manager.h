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
		size_t max_chunk_index_count;
		GLuint* chunk_indices;
		std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types;
		Chunk* chunks[RENDER_DISTANCE][RENDER_DISTANCE];
		std::queue<Chunk*> chunk_mesh_loading_queue;
		bool is_reloading;
	public:
		ChunkManager(std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types);
		ChunkManager(const ChunkManager& other) = delete;
		ChunkManager(ChunkManager&& rvalue) = delete;
		~ChunkManager() noexcept;
		void renderChunks();
		void updateChunkMeshQueue();
		void reloadChunkMesh();
		void pushToChunkMeshQueue(Chunk* chunk)
		{
			chunk_mesh_loading_queue.push(chunk);
		}

		Chunk* getChunk(const glm::vec2& chunk_pos)
		{
			Chunk* chunk = nullptr;
			if (0 <= chunk_pos.x && chunk_pos.x < RENDER_DISTANCE)
				if (0 <= chunk_pos.y && chunk_pos.y < RENDER_DISTANCE)
					chunk = chunks[(size_t)floor(chunk_pos.x)][(size_t)floor(chunk_pos.y)];
			if (chunk && chunk->getPos() == chunk_pos)
				return chunk;
			return nullptr;
		}
	};
}