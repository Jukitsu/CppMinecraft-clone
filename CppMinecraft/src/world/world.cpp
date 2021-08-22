#include "world.h"


namespace World
{
	using namespace Texturing;
	using BlockTypesPtr = std::shared_ptr<std::vector<Blocks::BlockType>>;

	World::World(const std::shared_ptr<TextureManager>& texture_manager)
		:texture_manager(texture_manager)
	{
		block_types = std::make_shared<std::vector<Blocks::BlockType>>();
		block_types->emplace_back(texture_manager, "Stone", 1,
			&models.cube, "res/textures/stone.png", false);
		block_types->emplace_back(texture_manager, "Grass", 2,
			&models.cube, "res/textures/grass.png", false);
		chunk_manager = std::make_unique<ChunkManager>(block_types);
		texture_manager->generateMipmaps();
		texture_manager->activate();
	}
	World::~World()
	{

	}

	void World::render()
	{
		chunk_manager->renderChunks();
	}
}