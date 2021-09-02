#pragma once
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/constants.hpp"

constexpr float pi = glm::pi<float>();

namespace Entity
{
	class Entity
	{
	protected:
		float speed;
		glm::vec3 position;
		glm::vec3 velocity;
		float yaw, pitch;
	public:
		Entity(const glm::vec3& spawn_pos, float facing_direction)
			// FACING DIRECTION: 0 = EAST, pi/2 = NORTH, pi = WEST, -pi/2 = SOUTH
			:position(spawn_pos), yaw(facing_direction), pitch(),
			speed(), velocity()
		{

		}

		virtual void updatePos(const glm::vec3& tpos, float delta_time)
		{
			float multiplier = speed * delta_time;
			position += multiplier * tpos;
		}

		float getYaw() { return yaw; }
		float getPitch() { return pitch; }
		const glm::vec3& getPos() { return position; }
		const glm::vec3& getVelocity() { return velocity; }

		void rotateYaw(float angle) 
		{
			yaw = glm::mod(yaw + angle, 2.0f * pi);
		}

		void rotatePitch(float angle)
		{
			pitch = std::max(-pi / 2, std::min(pi / 2, pitch + angle));
		}
	};
}