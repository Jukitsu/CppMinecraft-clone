#include "chunk.h"

namespace World
{	
	/* Chunk
	* Holder of the existing blocks in a 3D heap allocated array
	* this array uses numeric IDs to save memory
	* Uses a Mesh object to batch the block data to OpenGL
	*/
	using namespace Blocks;
	using BlockTypesPtr = std::array<Blocks::BlockType*, BLOCK_COUNT>*;

	Chunk::Chunk(const glm::vec3& cpos, BlockTypesPtr block_types, unsigned int* chunk_indices)
		:position(cpos), mesh(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6, 
			chunk_indices), block_types(block_types)
	{
		/* Initialize the 3D array*/
		blocks = new unsigned int** [CHUNK_WIDTH];
		for (unsigned int i = 0; i < CHUNK_WIDTH; i++) {
			blocks[i] = new unsigned int* [CHUNK_HEIGHT];
			for (unsigned int j = 0; j < CHUNK_HEIGHT; j++)
			{
				blocks[i][j] = new unsigned int[CHUNK_LENGTH];
				memset(blocks[i][j], 0, CHUNK_LENGTH);
			}
		}
		/* Allocate the buffers and pass the indices*/
		chunk_renderer.allocateBuffers(mesh);
	}
	/* Heavy copy constructor to avoid memory leaks. Might as well mark it at deleted though */
	Chunk::Chunk(const Chunk& other)
		:position(other.position), mesh(other.mesh), block_types(block_types)
	{
		blocks = new unsigned int** [CHUNK_WIDTH];
		for (unsigned int i = 0; i < CHUNK_WIDTH; i++) {
			blocks[i] = new unsigned int* [CHUNK_HEIGHT];
			for (unsigned int j = 0; j < CHUNK_HEIGHT; j++)
			{
				blocks[i][j] = new unsigned int[CHUNK_LENGTH];
				memcpy(blocks[i][j], other.blocks[i][j], CHUNK_LENGTH);
			}
		}
	}
	Chunk::~Chunk()
	{
		/* Delete the 3D array */
		std::cout << "Freeing Chunk Data" << '\n';
		if (blocks)
		{
			for (unsigned int i = 0; i < CHUNK_LENGTH; i++)
			{
				for (unsigned int j = 0; j < CHUNK_HEIGHT; j++)
					delete[] blocks[i][j];
				delete[] blocks[i];
			}
			delete[] blocks;
		}
	}	
	
	/* Chunk mesh batcher*/
	void Chunk::generate_mesh()
	{
		unsigned int block;
		unsigned int current_quad_count = 0;
		for (unsigned int lx = 0; lx < CHUNK_WIDTH; lx++)
			for (unsigned int ly = 0; ly < CHUNK_HEIGHT; ly++)
				for (unsigned int lz = 0; lz < CHUNK_LENGTH; lz++)
				{
					glm::vec3 lpos(lx, ly, lz);
					block = blocks[lx][ly][lz]; // get the block number of the block at that local position
					if (!block)
						continue;
					const BlockType& block_type = *(*block_types)[block]; // get its block type
					BatchInfo batch_info = {true, true, true, true, true, true};
					/* Face culling */
					if (block_type.is_cube)
					{
						batch_info.renderEast = !isOpaqueAt(lpos + glm::vec3(1, 0, 0));
						batch_info.renderWest = !isOpaqueAt(lpos + glm::vec3(-1, 0, 0));
						batch_info.renderUp = !isOpaqueAt(lpos + glm::vec3(0, 1, 0));
						batch_info.renderDown = !isOpaqueAt(lpos + glm::vec3(0, -1, 0));
						batch_info.renderNorth = !isOpaqueAt(lpos + glm::vec3(0, 0, -1));
						batch_info.renderSouth = !isOpaqueAt(lpos + glm::vec3(0, 0, 1));
					}
					/* Push the block quads in the mesh */
					current_quad_count = mesh.pushBlock(block_type, 
						glm::vec3(position.x * CHUNK_WIDTH, 
							position.y * CHUNK_HEIGHT,
							position.z * CHUNK_LENGTH) + lpos,
						current_quad_count, batch_info);
				}
		/* Batch the mesh vertex data */
		chunk_renderer.bufferBatch(mesh);
		chunk_renderer.bindLayout();
	}
	
}