#include "chunk_manager.h"

#include <random>


namespace World
{
	using ChunkPtr = std::shared_ptr<Chunk>;
	using BlockTypesPtr = std::array<Blocks::BlockType*, BLOCK_COUNT>*;
	ChunkManager::ChunkManager(BlockTypesPtr block_types)
		:block_types(block_types)
	{
		max_chunk_index_count = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6 * 6;
		chunk_indices = new unsigned int[max_chunk_index_count];
		for (unsigned int nquad = 0; nquad < max_chunk_index_count / 6; nquad++)
		{
			chunk_indices[nquad * 6] = 4 * nquad + 0;
			chunk_indices[nquad * 6 + 1] = 4 * nquad + 1;
			chunk_indices[nquad * 6 + 2] = 4 * nquad + 2;
			chunk_indices[nquad * 6 + 3] = 4 * nquad + 0;
			chunk_indices[nquad * 6 + 4] = 4 * nquad + 2;
			chunk_indices[nquad * 6 + 5] = 4 * nquad + 3;
		}
		for (unsigned int x = 0; x < 2; x++)
		{
			for (unsigned int z = 0; z < 2; z++)
			{
				glm::vec3 chunk_position{ x, 0, z };
				ChunkPtr current_chunk = std::make_shared<Chunk>(chunk_position, 
					block_types, chunk_indices);

				for (unsigned int i = 0; i < CHUNK_WIDTH; i++)
					for (unsigned int j = 0; j < CHUNK_HEIGHT; j++)
						for (unsigned int k = 0; k < CHUNK_LENGTH; k++)
						{
							if (j > 13)
								current_chunk->setBlock({ i, j, k }, (std::rand() % 2) ? 2 : 2);
							else
								current_chunk->setBlock({ i, j, k }, (std::rand() % 3) ? 1 : 1);
						}
				current_chunk->setBlock({ 0, 0, 0 }, 2);
				chunks.emplace_back(current_chunk);
			}
		}
		for (auto& chunk : chunks)
		{
			chunk->update_mesh();
		}
	}
	ChunkManager::~ChunkManager() noexcept
	{
		std::cout << "Freeing Chunk Manager Data\n";
		delete[] chunk_indices;
	}

	void ChunkManager::renderChunks()
	{
		for (auto& chunk : chunks)
		{
			chunk->draw();
		}
	}
}