#pragma once
#include "util/glm/glm.hpp"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 256
#define CHUNK_LENGTH 16

#define EAST glm::vec3(1, 0, 0)
#define WEST glm::vec3(-1, 0, 0)
#define NORTH glm::vec3(0, 0, -1)
#define SOUTH glm::vec3(0, 0, 1)
#define UP glm::vec3(0, 1, 0)
#define DOWN glm::vec3(0, -1, 0)


typedef glm::vec<3, unsigned char> Direction;
typedef glm::vec<3, int> Position;
typedef glm::vec<3, float> Vector3D;
typedef unsigned int BlockID;
typedef glm::mat4 Matrix4f;

std::array<Direction, 6> directions = {EAST, WEST, UP, DOWN, SOUTH, NORTH}