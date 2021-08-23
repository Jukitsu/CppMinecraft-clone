#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include "renderer/renderer.h"
#include "renderer/mesh.h"
#include "blocks/block_type.h"




namespace World
{
	constexpr int CHUNK_WIDTH = 16;
	constexpr int CHUNK_HEIGHT = 16;
	constexpr int CHUNK_LENGTH = 16;

	class Chunk
	{
		glm::vec3 position;
		std::shared_ptr<std::vector<Blocks::BlockType>> block_types;
		Rendering::Mesh mesh;
		Rendering::Renderer chunk_renderer;
		unsigned int ***blocks;
	public:
		Chunk(const glm::vec3& cpos, std::shared_ptr<std::vector<Blocks::BlockType>> block_types);
		Chunk(const Chunk& other); // Avoid copying chunks, its expensive af
		~Chunk() noexcept;

		int getBlock(const glm::vec3& pos) const;
		void setBlock(const glm::vec3& pos, int blockid);
		bool isOpaqueBlock(int blockid) const;
		bool isOpaqueAt(const glm::vec3& pos) const;
		void update_mesh();
		void draw();
	};
}
