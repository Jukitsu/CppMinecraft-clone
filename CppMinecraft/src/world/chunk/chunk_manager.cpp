#include "chunk_manager.h"

#include <random>


namespace World
{
	using ChunkPtr = std::shared_ptr<Chunk>;
	using BlockTypesPtr = std::shared_ptr<std::vector<Blocks::BlockType>>;
	ChunkManager::ChunkManager(const BlockTypesPtr& block_types)
		:block_types(block_types)
	{
		for (unsigned int x = 0; x < 2; x++)
		{
			for (unsigned int z = 0; z < 2; z++)
			{
				glm::vec3 chunk_position{ x, 0, z };
				ChunkPtr current_chunk = std::make_shared<Chunk>(std::move(chunk_position), block_types);

				for (unsigned int i = 0; i < CHUNK_WIDTH; i++)
					for (unsigned int j = 0; j < CHUNK_HEIGHT; j++)
						for (unsigned int k = 0; k < CHUNK_LENGTH; k++)
						{
							if (j > 13)
								current_chunk->setBlock({ i, j, k }, (std::rand() % 2) ? 2 : 2);
							else
								current_chunk->setBlock({ i, j, k }, (std::rand() % 3) ? 1 : 1);
						}
				chunks[((int)chunk_position.x << 16) ||
					((int)chunk_position.z)] = current_chunk;
			}
		}
		for (auto& [_, chunk] : chunks)
		{
			chunk->update_mesh();
		}
	}
	ChunkManager::~ChunkManager() noexcept
	{

	}

	void ChunkManager::renderChunks()
	{
		for (auto& [_, chunk] : chunks)
		{
			chunk->draw();
		}
	}
}