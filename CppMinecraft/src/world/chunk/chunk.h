#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include "renderer/renderer.h"
#include "renderer/mesh.h"
#include "blocks/block_type.h"
#include "renderer/batch_info.h"




namespace World
{
	constexpr int CHUNK_WIDTH = 16;
	constexpr int CHUNK_HEIGHT = 32;
	constexpr int CHUNK_LENGTH = 16;

	constexpr int BLOCK_COUNT = 3;

	class Chunk
	{
		glm::vec3 position;
		std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types;
		Rendering::Renderer chunk_renderer;
		unsigned int ***blocks;
	public:
		Rendering::Mesh mesh;

		Chunk(const glm::vec3& cpos, std::array<Blocks::BlockType*, BLOCK_COUNT>* block_types,
			unsigned int* chunk_indices);
		Chunk(const Chunk& other); // Avoid copying chunks, its expensive af
		~Chunk() noexcept;

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
		void generate_mesh();

		void draw()
		{
			/* Draw call */
			chunk_renderer.draw(mesh.current_index_count);
		}
	};
}
