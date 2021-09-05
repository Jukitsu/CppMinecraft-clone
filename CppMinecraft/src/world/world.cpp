#include "world.h"


namespace World
{
	/* World Manager
	* Contains some really basic stuff, such as the 
	* Chunk Manager and the block models
	*/
	using namespace Texturing;
	using BlockTypesPtr = std::array<Blocks::BlockType*, BLOCK_COUNT>;

	World::World(const std::shared_ptr<TextureManager>& texture_manager)
		:texture_manager(texture_manager)
	{
		/* Initializing textures*/
		std::cout << "Initializing textures\n";
		texture_manager->addTexture("res/textures/cobblestone.png"); // ID: 0
		texture_manager->addTexture("res/textures/stone.png"); // ID: 1
		texture_manager->addTexture("res/textures/grass.png"); // ID: 2
		texture_manager->addTexture("res/textures/grass_side.png"); // ID: 3
		texture_manager->addTexture("res/textures/dirt.png"); // ID: 4
		texture_manager->addTexture("res/textures/cobblestone.png"); // ID: 5
		texture_manager->addTexture("res/textures/planks.png"); // ID: 6

		/* Initializing the block models */
		std::cout << "Initializing the block models\n";
		block_types[0] = new Blocks::BlockType("Air", 0,
			&models.air, {}, true, false);
		block_types[1] = new Blocks::BlockType("Stone", 1,
			&models.cube, { 1, 1, 1, 1, 1, 1 }, false, true);
		block_types[2] = new Blocks::BlockType("Grass", 2,
			&models.cube, { 3, 3, 2, 4, 3, 3 }, false, true);
		block_types[3] = new Blocks::BlockType("Dirt", 3,
			&models.cube, { 4, 4, 4, 4, 4, 4 }, false, true);
		block_types[4] = new Blocks::BlockType("Cobblestone", 4, 
			&models.cube, { 5, 5, 5, 5, 5, 5 }, false, true);
		block_types[5] = new Blocks::BlockType("Planks", 5,
			&models.cube, { 6, 6, 6, 6, 6, 6 }, false, true);
		chunk_manager = std::make_unique<ChunkManager>(&block_types);
		texture_manager->generateMipmaps();
		texture_manager->activate();
	}
	World::~World()
	{
		std::cout << "Freeing the block models\n";
		for (Blocks::BlockType* block_type : block_types)
			delete block_type;
	}
	int World::getBlock(const glm::vec3& pos)
	{
		glm::vec2 cpos = to_chunk_pos(pos);
		glm::vec3 lpos = to_local_pos(pos);
		Chunk* chunk = chunk_manager->getChunk(cpos);
		if (chunk)
		{
			return chunk->getBlock(lpos);
		}
		return 0;
	}

	void World::setBlock(const glm::vec3& pos, int block)
	{
		glm::vec2 cpos = to_chunk_pos(pos);
		glm::vec3 lpos = to_local_pos(pos);
		Chunk* chunk = chunk_manager->getChunk(cpos);
		if (chunk)
		{
			chunk->setBlock(lpos, block);
			chunk->resetIndexCount();
			chunk->update_subchunks_at(lpos);
		}
	}

}