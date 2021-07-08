#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <util/glm/glm.hpp>
#include "util/glm/gtc/matrix_transform.hpp"
#include <util/glm/gtc/constants.hpp>
#include <util/glm/trigonometric.hpp>
#include "renderer/gl/shader.h"
#include "renderer/gl/glErrors.h"


class Camera {
public:
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 mvp;
	glm::vec3 input;
	glm::vec3 position; 
	GLsizei width;
	GLsizei height;
	ShaderProgram *shader_program;
	GLdouble yaw;
	GLdouble pitch;
	Camera(ShaderProgram* shader_program, GLsizei width, GLsizei height);
	~Camera();
	void reset_matrices();
	void rotate_yaw(double angle);
	void rotate_pitch(double angle);
	void update_matrices();
	void load_matrices();
};