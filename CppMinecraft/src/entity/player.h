#pragma once

#include <cmath>

#include "entity.h"

namespace Entity
{
	class Player : public Entity
	{
	public:
		Player(const glm::vec3& spawn_pos);
		~Player();
		void updatePos(const glm::vec3& tpos, float delta_time) override;
	};
}
