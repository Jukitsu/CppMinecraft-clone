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
	/* Encapsulation stuff */
	int Chunk::getBlock(const glm::vec3& pos) const
	{
		int x = pos.x, y = pos.y, z = pos.z;
		if ((x >= 0) && (y >= 0) && (z >= 0))
			if ((x < CHUNK_WIDTH) && (y < CHUNK_HEIGHT) && (z < CHUNK_LENGTH))
				return blocks[x][y][z];
		return 0;
	}
	void Chunk::setBlock(const glm::vec3& pos, int blockid)
	{
		unsigned int x = pos.x, y = pos.y, z = pos.z;
		if ((x >= 0) && (y >= 0) && (z >= 0))
			if ((x < CHUNK_WIDTH) && (y < CHUNK_HEIGHT) && (z < CHUNK_LENGTH))
				blocks[x][y][z] = blockid;
	}
	/* Some stuff to make easier batching*/
	bool Chunk::isOpaqueBlock(int blockid) const
	{
		return !(*block_types)[blockid]->is_transparent;
	}
	bool Chunk::isOpaqueAt(const glm::vec3& pos) const
	{
		return isOpaqueBlock(getBlock(pos));
	}

	/* Chunk mesh batcher*/
	void Chunk::update_mesh()
	{
		mesh.clear(); // To remove
		int block;
		unsigned int current_quad_count = 0;
		for (unsigned int lx = 0; lx < CHUNK_WIDTH; lx++)
			for (unsigned int ly = 0; ly < CHUNK_HEIGHT; ly++)
				for (unsigned int lz = 0; lz < CHUNK_LENGTH; lz++)
				{
					glm::vec3 pos(lx, ly, lz);
					block = blocks[lx][ly][lz]; // get the block number of the block at that local position
					if (!block)
						continue;
					const BlockType& block_type = *(*block_types)[block]; // get its block type
					BatchInfo batch_info = {true, true, true, true, true, true};
					/* Face culling */
					if (block_type.is_cube)
					{
						batch_info.renderEast = !isOpaqueAt(pos + glm::vec3(1, 0, 0));
						batch_info.renderWest = !isOpaqueAt(pos + glm::vec3(-1, 0, 0));
						batch_info.renderUp = !isOpaqueAt(pos + glm::vec3(0, 1, 0));
						batch_info.renderDown = !isOpaqueAt(pos + glm::vec3(0, -1, 0));
						batch_info.renderNorth = !isOpaqueAt(pos + glm::vec3(0, 0, 1));
						batch_info.renderSouth = !isOpaqueAt(pos + glm::vec3(0, 0, -1));
					}
					/* Push the block quads in the mesh */
					current_quad_count = mesh.pushBlock(block_type, 
							16.0f*position + glm::vec3(lx, ly, lz), current_quad_count, batch_info);
				}
		/* Batch the mesh vertex data */
		chunk_renderer.bufferBatch(mesh);
		chunk_renderer.bindLayout();
	}
	void Chunk::draw()
	{
		/* Bind the VAO, VBO and IBOs*/
		chunk_renderer.bindAll();
		/* Draw call */
		chunk_renderer.draw(mesh.current_index_count);
	}
}