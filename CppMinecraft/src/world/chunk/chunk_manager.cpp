#include "chunk_manager.h"

#include <random>


namespace World
{
	/* Chunk Manager
	* Wrapper that holds the existing Chunks 
	* and the chunk universal indices
	* Contains the World generator for now
	*/
	using BlockTypesPtr = std::array<Blocks::BlockType*, BLOCK_COUNT>*;

	ChunkManager::ChunkManager(BlockTypesPtr block_types)
		:block_types(block_types)
	{
		/* Create the chunk universal indices */
		max_chunk_index_count = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6 * 6;
		chunk_indices = new GLuint[max_chunk_index_count];
		for (GLuint nquad = 0; nquad < max_chunk_index_count / 6; nquad++)
		{
			chunk_indices[nquad * 6] = 4 * nquad + 0;
			chunk_indices[nquad * 6 + 1] = 4 * nquad + 1;
			chunk_indices[nquad * 6 + 2] = 4 * nquad + 2;
			chunk_indices[nquad * 6 + 3] = 4 * nquad + 0;
			chunk_indices[nquad * 6 + 4] = 4 * nquad + 2;
			chunk_indices[nquad * 6 + 5] = 4 * nquad + 3;
		}
		/* World generation */
		{
			std::cout << "Generating world and loading chunks\n";
			Chunk* west_chunk;
			Chunk* north_chunk;
			for (int x = 0; x < RENDER_DISTANCE; x++)
				for (int z = 0; z < RENDER_DISTANCE; z++)
				{
					glm::vec2 chunk_position{ x, z };
					Chunk* current_chunk = new Chunk(chunk_position,
						block_types, chunk_indices);
					for (size_t i = 0; i < CHUNK_WIDTH; i++)
						for (size_t j = 0; j < CHUNK_HEIGHT; j++)
							for (size_t k = 0; k < CHUNK_LENGTH; k++)
							{
								if (j > SEA_LEVEL)
									current_chunk->setBlock({ i, j, k }, 0);
								else if (j >= SEA_LEVEL)
									current_chunk->setBlock({ i, j, k }, 2);
								else if (j >= (SEA_LEVEL - 3))
									current_chunk->setBlock({ i, j, k }, 3);
								else
									current_chunk->setBlock({ i, j, k }, 1);
							}
					chunks[x][z] = current_chunk;
					pushToChunkMeshQueue(current_chunk);
					if (z > 0)
					{
						north_chunk = chunks[x][z - 1];
						current_chunk->neighbour_chunks.north = north_chunk;
						north_chunk->neighbour_chunks.south = current_chunk;
					}
					if (x > 0)
					{
						west_chunk = chunks[x - 1][z];
						current_chunk->neighbour_chunks.west = west_chunk;
						west_chunk->neighbour_chunks.east = current_chunk;
					}
				}
		}
	}
	ChunkManager::~ChunkManager() noexcept
	{
		std::cout << "Freeing Chunk Manager Data\n";
		delete[] chunk_indices;
		Chunk* chunk;
		for (size_t x = 0; x < RENDER_DISTANCE; x++)
			for (size_t z = 0; z < RENDER_DISTANCE; z++)
			{
				chunk = chunks[x][z];
				delete chunk;
			}
	}
	/* Pretty straightforward stuff too */
	void ChunkManager::updateChunkMeshQueue()
	{
		/* Batch the chunk meshes */
		if (!chunk_mesh_loading_queue.empty())
		{
			Chunk* chunk = chunk_mesh_loading_queue.front();
			chunk_mesh_loading_queue.pop();
			chunk->generate_mesh();
			return;
		}
		is_reloading = false;
	}
	void ChunkManager::renderChunks()
	{
		for (int x = 0; x < RENDER_DISTANCE; x++)
			for (int z = 0; z < RENDER_DISTANCE; z++)
				chunks[x][z]->draw();
	}
	void ChunkManager::reloadChunkMesh()
	{
		if (is_reloading)
		{
			return;
		}
		Chunk* chunk;
		for (int x = 0; x < RENDER_DISTANCE; x++)
			for (int z = 0; z < RENDER_DISTANCE; z++)
			{
				chunk = chunks[x][z];
				chunk->resetIndexCount();
				chunk_mesh_loading_queue.push(chunk);
			}
		is_reloading = true;
	}
}