#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <util/glm/glm.hpp>
#include "gl/glErrors.h"
#include "gl/shader.h"

class Camera {
	ShaderProgram shader_program;
	int width;
	int height;
};