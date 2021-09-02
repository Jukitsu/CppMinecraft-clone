#include "hit.h"

namespace Entity
{
	PlayerHitray::PlayerHitray(World::World* world)
		:world(world), vector{0, 0, 0},
		position(0), block(position), distance(0u)
	{

	}
	bool PlayerHitray::check(float distance, 
		const glm::vec3& current_block, const glm::vec3& next_block)
	{
		if (world->getBlock(next_block))
			return true;
		else
		{
			position += ((float)distance * vector);
			block = next_block;
			this->distance += distance;
			return false;
		}
	}
	bool PlayerHitray::step()
	{
		glm::vec3 sign = { 1, 1, 1 };
		glm::vec3 lpos = position - block;
		glm::vec3 abs_vector = vector;

		for (unsigned short i = 0; i < 3; i++)
		{
			if (vector[i] < 0)
			{
				sign[i] = -1;

				abs_vector[i] = -abs_vector[i];
				lpos[i] = -lpos[i];
			}
		}
		if (abs_vector.x)
		{
			float x = 0.5f;
			float y = (0.5f - lpos.x) / abs_vector.x * abs_vector.y + lpos.y;
			float z = (0.5f - lpos.x) / abs_vector.x * abs_vector.z + lpos.z;

			if (y >= -0.5f && y <= 0.5f && z >= -0.5f && z <= 0.5f)
			{
				float distance = std::sqrt(std::pow((x - lpos.x), 2)
					+ std::pow((y - lpos.y), 2)
					+ std::pow((z - lpos.z), 2));



				return check(distance, block, { block.x + sign.x, block.y, block.z });
			}
		}
		if (abs_vector.y)
		{
			float x = (0.5f - lpos.y) / abs_vector.y * abs_vector.x + lpos.x;
			float y = 0.5f;
			float z = (0.5f - lpos.y) / abs_vector.y * abs_vector.z + lpos.z;

			if (x >= -0.5f && x <= 0.5f && z >= -0.5f && z <= 0.5f)
			{
				float distance = std::sqrt(std::pow((x - lpos.x), 2)
					+ std::pow((y - lpos.y), 2)
					+ std::pow((z - lpos.z), 2));



				return check(distance, block, { block.x, block.y + sign.y, block.z });
			}
		}
		if (abs_vector.z)
		{
			float x = (0.5 - lpos.z) / abs_vector.z * abs_vector.x + lpos.x;
			float y = (0.5 - lpos.z) / abs_vector.z * abs_vector.y + lpos.y;
			float z = 0.5f;

			if (x >= -0.5f && x <= 0.5f && y >= -0.5f && y <= 0.5f)
			{
				float distance = std::sqrt(std::pow((x - lpos.x), 2)
					+ std::pow((y - lpos.y), 2)
					+ std::pow((z - lpos.z), 2));



				return check(distance, block, { block.x, block.y, block.z + sign.z });
			}
		}
	}
}
