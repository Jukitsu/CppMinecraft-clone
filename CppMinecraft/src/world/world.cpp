#include "world.h"


namespace World
{
	using namespace Texturing;
	using BlockTypesPtr = std::array<Blocks::BlockType*, BLOCK_COUNT>;

	World::World(const std::shared_ptr<TextureManager>& texture_manager)
		:texture_manager(texture_manager)
	{
		std::cout << "Initialising the block models\n";
		block_types[0] = new Blocks::BlockType(texture_manager, "Air", 0,
			&models.cube, "res/textures/cobblestone.png", true, false);
		block_types[1] = new Blocks::BlockType(texture_manager, "Stone", 1,
			&models.cube, "res/textures/stone.png", false, true);
		block_types[2] = new Blocks::BlockType(texture_manager, "Grass", 2,
			&models.cube, "res/textures/grass.png", false, true);
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

	void World::render()
	{
		chunk_manager->renderChunks();
	}
}