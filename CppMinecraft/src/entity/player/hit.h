#pragma once

#include <cmath>
#include <functional>

#include "world/world.h"


namespace Entity
{
	constexpr unsigned short HIT_RANGE = 3;
	class PlayerHitray
	{
	public:
		World::World* world;
		glm::vec3 vector;
		glm::vec3 position;
		glm::vec3 block;
		float distance;
		PlayerHitray(World::World* world);
		~PlayerHitray() noexcept
		{

		}
		void update(float yaw, float pitch, const glm::vec3& starting_pos)
		{
			vector = glm::vec3(std::cos(yaw) * std::cos(pitch),
				std::sin(pitch),
				std::sin(yaw) * std::cos(pitch));
			position = starting_pos;
			block = position;
			distance = 0u;
		}
		bool check(float distance, 
			const glm::vec3& current_block, const glm::vec3& next_block);
		bool step();
	};
}