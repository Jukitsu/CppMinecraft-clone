#include "chunk.h"
#include "chunk_manager.h"

namespace World
{	
	/* Chunk
	* Holder of the existing blocks in a 3D heap allocated array
	* this array uses numeric IDs to save memory
	* Uses several meshes (regions) to batch the block data to OpenGL
	*/
	using namespace Blocks;
	using BlockTypes = std::array<BlockType*, BLOCK_COUNT>;
	
	Subchunk::Subchunk()
		:mesh(CHUNK_WIDTH * ( CHUNK_HEIGHT / SUBCHUNK_COUNT) * CHUNK_LENGTH * 6),
		offset(0)
	{

	}

	Subchunk::~Subchunk() noexcept
	{

	}

	Chunk::Chunk(const glm::vec2& cpos, BlockTypes* block_types, uint32_t* chunk_indices)
		:position(cpos), block_types(block_types) 
	{
		/* Initialize the 3D array*/
		blocks = new uint32_t** [CHUNK_WIDTH];
		for (uint32_t i = 0; i < CHUNK_WIDTH; i++)
		{
			blocks[i] = new uint32_t * [CHUNK_HEIGHT];
			for (uint32_t j = 0; j < CHUNK_HEIGHT; j++)
			{
				blocks[i][j] = new uint32_t[CHUNK_LENGTH];
				memset(blocks[i][j], 0, CHUNK_LENGTH);
			}
		}
		size_t max_quads = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6;
		size_t max_vertex_count = 0;
		size_t max_index_count = max_quads * 6;
		/* Allocate the buffers and pass the indices*/
		chunk_renderer.allocateBuffers(max_vertex_count, max_index_count, chunk_indices);
		chunk_renderer.bindLayout();
	}

	Chunk::~Chunk()
	{
		/* Delete the 3D array */
		std::cout << "Freeing Chunk Data" << '\n';
		if (blocks)
		{
			for (uint32_t i = 0; i < CHUNK_LENGTH; i++)
			{
				for (uint32_t j = 0; j < CHUNK_HEIGHT; j++)
					delete[] blocks[i][j];
				delete[] blocks[i];
			}
			delete[] blocks;
		}
	}	

	inline bool Chunk::isOutOfChunk(const glm::vec3& pos)
	{
		return (pos.x < 0 || pos.x >= CHUNK_WIDTH
			|| pos.y < 0 || pos.y >= CHUNK_HEIGHT
			|| pos.z < 0 || pos.z >= CHUNK_LENGTH);
	}

	inline bool Chunk::canRenderFacing(const glm::vec3& facing_pos)
	{
		if (!isOutOfChunk(facing_pos))
			return !isOpaqueAt(facing_pos);		
		return _canRenderFacingNeighbour(facing_pos);
	}

	bool Chunk::_canRenderFacingNeighbour(const glm::vec3& facing_pos)
	{
		if (facing_pos.x == -1)
		{
			if (neighbour_chunks.west)
			{
				return !neighbour_chunks.west->isOpaqueAt({ CHUNK_WIDTH - 1, facing_pos.y, facing_pos.z });
			}
		}
		else if (facing_pos.x == CHUNK_WIDTH)
		{
			if (neighbour_chunks.east)
			{
				return !neighbour_chunks.east->isOpaqueAt({ 0, facing_pos.y, facing_pos.z });
			}
		}
		else if (facing_pos.z == -1)
		{
			if (neighbour_chunks.north)
			{
				return !neighbour_chunks.north->isOpaqueAt({ facing_pos.x, facing_pos.y, CHUNK_LENGTH - 1 });
			}
		}
		else if (facing_pos.z == CHUNK_LENGTH)
		{
			if (neighbour_chunks.south)
			{
				return !neighbour_chunks.south->isOpaqueAt({ facing_pos.x, facing_pos.y, 0 });
			}
		}
		return true;
	}
	
	
	/* Chunk mesh batcher*/
	void Chunk::update_subchunks_at(const glm::vec3& local_pos)
	{
		generate_mesh(local_pos.y / (CHUNK_HEIGHT / SUBCHUNK_COUNT));
	}
	void Chunk::generate_mesh(uint8_t sy, uint8_t end)
	{
		uint16_t block;
		uint32_t current_quad_count = 0;
		for (uint16_t i = 0u; sy && (i < sy); i++)
			current_quad_count += subchunks[i].getMesh().current_quad_count;

		for (sy; sy < end; sy++)
		{
			Subchunk& subchunk = subchunks[sy];
			subchunk.getMesh().clear();
			subchunk.setOffset(current_quad_count * 4);
			uint32_t ly;
			for (uint32_t sly = 0; sly < (CHUNK_HEIGHT / SUBCHUNK_COUNT); sly++)
				for (uint32_t lx = 0; lx < CHUNK_WIDTH; lx++)
					for (uint32_t lz = 0; lz < CHUNK_LENGTH; lz++)
			{
				ly = sy * (CHUNK_HEIGHT / SUBCHUNK_COUNT) + sly;
				glm::vec3 lpos(lx, ly, lz);
				block = blocks[lx][ly][lz]; // get the block number of the block at that local position
				if (!block)
					continue;
				const BlockType& block_type = *(*block_types)[block]; // get its block type
				BatchInfo batch_info = { true, true, true, true, true, true };
				/* Face culling */
				if (block_type.is_cube)
				{
					batch_info.renderEast = canRenderFacing(lpos + glm::vec3(1, 0, 0));
					batch_info.renderWest = canRenderFacing(lpos + glm::vec3(-1, 0, 0));
					batch_info.renderUp = canRenderFacing(lpos + glm::vec3(0, 1, 0));
					batch_info.renderDown = canRenderFacing(lpos + glm::vec3(0, -1, 0));
					batch_info.renderNorth = canRenderFacing(lpos + glm::vec3(0, 0, -1));
					batch_info.renderSouth = canRenderFacing(lpos + glm::vec3(0, 0, 1));
				}
				subchunk.pushBlock(block_type, 
					to_world_pos(position, lpos), batch_info);
			}
			current_quad_count += subchunk.getMesh().current_quad_count;
		}
		/* Batch the mesh vertex data */
		if (current_quad_count * 4 * sizeof(Geometry::Vertex) > chunk_renderer.getVBOsize())
		{
			chunk_renderer.reallocVBO(current_quad_count * 4 + ((CHUNK_HEIGHT / SUBCHUNK_COUNT) * sizeof(int)));
			generate_mesh(0, sy);
		}

		for (Subchunk& subchunk: subchunks)
			chunk_renderer.bufferBatch(subchunk.getMesh(), subchunk.getOffset());

		index_count = current_quad_count * 6;
	}
}