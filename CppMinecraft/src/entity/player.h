#pragma once

#include <cmath>

#include "entity.h"

namespace Entity
{
	class Player : public Entity
	{
	public:
		Player(const glm::vec3& spawn_pos)
			:Entity(spawn_pos, pi / 2)
		{
			speed = 7;
			pitch = 0.0f;
		}

		~Player()
		{

		}

		void updatePos(const glm::vec3& input, float delta_time) override
		{
			float angle;
			float multiplier = speed * (float)delta_time;
			position.y += input.y * multiplier;
			if (input.x || input.z) {
				angle = yaw + std::atan2(input.z, input.x) - pi / 2;
				position.x += glm::cos(angle) * multiplier;
				position.z += glm::sin(angle) * multiplier;
			}
		}
	};
}
