#include "chunk.h"

namespace World
{
	using namespace Blocks;
	using BlockTypesPtr = std::shared_ptr<std::vector<Blocks::BlockType>>;

	Chunk::Chunk(glm::vec3&& cpos, BlockTypesPtr block_types)
		:position(cpos), mesh(CHUNK_WIDTH* CHUNK_HEIGHT* CHUNK_LENGTH * 6), block_types(block_types)
	{
		blocks = new unsigned int** [CHUNK_WIDTH];
		for (unsigned int i = 0; i < CHUNK_WIDTH; i++) {
			blocks[i] = new unsigned int* [CHUNK_HEIGHT];
			for (unsigned int j = 0; j < CHUNK_HEIGHT; j++)
			{
				blocks[i][j] = new unsigned int[CHUNK_LENGTH];
				memset(blocks[i][j], 0, CHUNK_LENGTH);
			}
		}
	}
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

	int Chunk::getBlock(const glm::vec3& pos) const
	{
		return blocks[(unsigned int)pos.x][(unsigned int)pos.y][(unsigned int)pos.z];
	}
	void Chunk::setBlock(const glm::vec3& pos, int blockid)
	{
		blocks[(unsigned int)pos.x][(unsigned int)pos.y][(unsigned int)pos.z] = blockid;
	}
	bool Chunk::isOpaqueBlock(int blockid) const
	{
		return !(*block_types)[blockid].is_transparent;
	}
	bool Chunk::isOpaqueAt(const glm::vec3& pos) const
	{
		return isOpaqueBlock(getBlock(pos));
	}
	void Chunk::update_mesh()
	{
		mesh.clear();
		int block;
		unsigned int current_quad_count = 0;
		for (unsigned int lx = 0; lx < CHUNK_WIDTH; lx++)
			for (unsigned int ly = 0; ly < CHUNK_HEIGHT; ly++)
				for (unsigned int lz = 0; lz < CHUNK_LENGTH; lz++)
				{
					block = blocks[lx][ly][lz]; // get the block number of the block at that local position
					if (!block)
						continue;
					const BlockType& block_type = (*block_types)[block]; // get the block type
					current_quad_count = mesh.pushBlock(block_type, 
						16.0f*position + glm::vec3(lx, ly, lz), current_quad_count);
				}
		if (current_quad_count * 6 != mesh.getIndices().size())
			std::cout << "Invalid mesh" << '\n';
		std::cout << "Quad count: " << current_quad_count << '\n';
		chunk_renderer.bufferData(mesh);
		chunk_renderer.bindLayout();
	}
	void Chunk::draw()
	{
		chunk_renderer.bindAll();
		chunk_renderer.draw();
	}
}