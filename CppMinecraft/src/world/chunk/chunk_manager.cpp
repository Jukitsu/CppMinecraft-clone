#include "chunk_manager.h"

#include <random>


namespace World
{
	/* Chunk Manager
	* Wrapper that holds the existing Chunks 
	* and the chunk universal indices
	* Contains the World generator for now
	*/
	using ChunkPtr = std::shared_ptr<Chunk>;
	using BlockTypesPtr = std::array<Blocks::BlockType*, BLOCK_COUNT>*;

	ChunkManager::ChunkManager(BlockTypesPtr block_types)
		:block_types(block_types)
	{
		/* Create the chunk universal indices */
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
		/* World generation */
		std::cout << "Generating world and loading chunks\n";
		for (int z = 0; z < 8; z++)
			for (int x = 0; x < 8; x++)
		{
			glm::vec3 chunk_position{ x, 0, -z };
			ChunkPtr current_chunk = std::make_shared<Chunk>(chunk_position, 
				block_types, chunk_indices);

			for (unsigned int i = 0; i < CHUNK_WIDTH; i++)
				for (unsigned int j = 0; j < CHUNK_HEIGHT; j++)
					for (unsigned int k = 0; k < CHUNK_LENGTH; k++)
					{
						if (j > (CHUNK_HEIGHT - 3))
							current_chunk->setBlock({ i, j, k }, (std::rand() % 2) ? 0 : 2);
						else
							current_chunk->setBlock({ i, j, k }, (std::rand() % 3) ? 0 : 1);
					}
			chunks.emplace_back(current_chunk);
		}
		for (auto& chunk : chunks)
		{
			chunk_mesh_loading_queue.push(chunk);
		}
	}
	ChunkManager::~ChunkManager() noexcept
	{
		std::cout << "Freeing Chunk Manager Data\n";
		delete[] chunk_indices;
	}
	/* Pretty straightforward stuff too */
	void ChunkManager::updateChunkMeshQueue()
	{
		/* Batch the chunk meshes */
		if (!chunk_mesh_loading_queue.empty())
		{
			auto& chunk = chunk_mesh_loading_queue.front();
			chunk_mesh_loading_queue.pop();
			chunk->generate_mesh();
		}
	}
	void ChunkManager::renderChunks()
	{
		for (auto& chunk : chunks)
		{
			chunk->draw();
		}
	}
	void ChunkManager::reloadChunkMesh()
	{
		while (!chunk_mesh_loading_queue.empty())
		{
			chunk_mesh_loading_queue.pop();
		}
		for (auto& chunk : chunks)
		{
			chunk->mesh.clear();
			chunk_mesh_loading_queue.push(chunk);
		}
	}
}