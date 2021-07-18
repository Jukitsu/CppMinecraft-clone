#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "texture/texture_manager.h"

typedef int Model;

struct Block {
	TextureManager* texture_manager;
	std::string textures_filepath[8];
	Model model;
};

