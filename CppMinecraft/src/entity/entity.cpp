#include "entity.h"

namespace Entity
{
	Entity::Entity(const glm::vec3& spawn_pos, float facing_direction)
		// FACING DIRECTION: 0 = EAST, pi/2 = NORTH, pi = WEST, -pi/2 = SOUTH
		:position(spawn_pos), yaw(facing_direction), pitch(),
		speed(), velocity()
	{

	}

	void Entity::updatePos(const glm::vec3& tpos, float delta_time)
	{
		float multiplier = speed * delta_time;
		position += multiplier * tpos;
	}

	float Entity::getYaw() { return yaw; }
	float Entity::getPitch() { return pitch; }
	const glm::vec3& Entity::getPos() { return position; }
	const glm::vec3& Entity::getVelocity() { return velocity; }

	void Entity::rotateYaw(float angle) {
		yaw = glm::mod(yaw + angle, 2.0f * pi);
	}

	void Entity::rotatePitch(float angle) {
		pitch = std::max(-pi / 2, std::min(pi / 2, pitch + angle));
	}
}