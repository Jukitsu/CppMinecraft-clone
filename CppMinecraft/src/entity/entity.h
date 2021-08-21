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
		Entity(const glm::vec3& spawn_pos, float facing_direction);
		float getYaw(), getPitch();
		const glm::vec3& getPos(), &getVelocity();
		virtual void updatePos(const glm::vec3& tpos, float delta_time);
		void rotateYaw(float angle);
		void rotatePitch(float angle);
	};
}