#pragma once

#include <cmath>

#include "glm/glm.hpp"

#include "constants.h"

namespace World
{
	inline glm::vec3 to_world_pos(const glm::vec2& chunk_pos, const glm::vec3& local_pos)
	{
		return glm::vec3(chunk_pos.x * CHUNK_WIDTH,
			0 ,
			chunk_pos.y * CHUNK_LENGTH) + local_pos;
	}

	inline glm::vec2 to_chunk_pos(const glm::vec3& world_pos)
	{
		return glm::vec2(floor(world_pos.x / CHUNK_WIDTH),
			floor(world_pos.z / CHUNK_LENGTH));
	}

	inline glm::vec3 to_local_pos(const glm::vec3& world_pos)
	{
		return glm::vec3((float)((int)world_pos.x % CHUNK_WIDTH),
			(float)((int)world_pos.y % CHUNK_HEIGHT),
			(float)((int)world_pos.z % CHUNK_LENGTH));
	}
} 