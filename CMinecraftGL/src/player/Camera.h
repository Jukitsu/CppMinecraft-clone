#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <util/glm/glm.hpp>
#include "util/glm/gtc/matrix_transform.hpp"
#include <util/glm/gtc/constants.hpp>
#include <util/glm/trigonometric.hpp>
#include "renderer/gl/shader.h"
#include "renderer/gl/glErrors.h"


class Camera {
public:
	glm::mat4 proj, view, model;
	glm::vec3 input;
	glm::vec3 position; 
	GLubyte proj_loc, view_loc, model_loc;
	GLsizei width, height;
	ShaderProgram *shader_program;
	GLdouble yaw, pitch;
	Camera();
	Camera(ShaderProgram *shader_program, GLsizei width, GLsizei height);
	~Camera();
	void update_dim(GLsizei width, GLsizei height);
	void rotate_yaw(double angle);
	void rotate_pitch(double angle);
	void update_matrices();
	void load_matrices();
	void poll_input(const glm::vec3 &tvec);
	void reset_input();
	void update_pos(double delta_time);
};