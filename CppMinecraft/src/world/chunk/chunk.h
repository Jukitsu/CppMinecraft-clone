#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include "renderer/renderer.h"
#include "renderer/mesh.h"
#include "blocks/block_type.h"
#include "renderer/batch_info.h"


#include "constants.h"

#include "chunk_math.h"


namespace World
{

	class Chunk
	{
		glm::vec2 position;
		std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types;
		Rendering::Renderer chunk_renderer;
		unsigned int ***blocks;
		Rendering::Mesh mesh;
	public:
		struct _neighbourChunks {
			Chunk* east;
			Chunk* west;
			Chunk* south;
			Chunk* north;
		} neighbour_chunks;

		

		Chunk(const glm::vec2& cpos, std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types,
			unsigned int* chunk_indices);
		Chunk(const Chunk& other) = delete; // Avoid copying chunks, its expensive af
		~Chunk() noexcept;

		void clearMeshes()
		{
			mesh.clear();
		}
		const glm::vec2& getPos()
		{
			return position;
		}
		int getBlock(const glm::vec3& pos) const
		{
			int x = pos.x, y = pos.y, z = pos.z;
			if ((x >= 0) && (y >= 0) && (z >= 0))
				if ((x < CHUNK_WIDTH) && (y < CHUNK_HEIGHT) && (z < CHUNK_LENGTH))
					return blocks[x][y][z];
			return 0;
		}
		void setBlock(const glm::vec3& pos, unsigned int blockid, bool update = false)
		{
			unsigned int x = pos.x, y = pos.y, z = pos.z;
			if ((x >= 0) && (y >= 0) && (z >= 0))
				if ((x < CHUNK_WIDTH) && (y < CHUNK_HEIGHT) && (z < CHUNK_LENGTH))
					blocks[x][y][z] = blockid;

		}
		bool isOpaqueBlock(unsigned int blockid) const
		{
			return !(*block_types)[blockid]->is_transparent;
		}
		bool isOpaqueAt(const glm::vec3& pos) const
		{
			return isOpaqueBlock(getBlock(pos));
		}
	private:
		inline bool isOutOfChunk(const glm::vec3& local_pos);
		inline bool canRenderFacing(const glm::vec3& facing_pos);
		bool _canRenderFacingNeighbour(const glm::vec3& facing_pos);

	public:
		void generate_mesh();

		void draw()
		{
			/* Draw call */
			chunk_renderer.draw(mesh.current_quad_count * 6);
		}
	};
}
