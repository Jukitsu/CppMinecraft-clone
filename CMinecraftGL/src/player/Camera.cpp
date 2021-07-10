#include "Camera.h"


const double pi = glm::pi<double>();

Camera::Camera(ShaderProgram* shader_program, GLsizei width, GLsizei height)
	:shader_program(shader_program), input(0, 2, -2),
	position(0, 0, 0), yaw(0.0), pitch(pi/4),
	proj(1.0f), view(1.0f), model(1.0f), width(width),
	height(height), proj_loc(), view_loc(), model_loc()
{
	proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::mat4(1.0f);
	proj_loc = shader_program->find_uniform("proj");
	view_loc = shader_program->find_uniform("view");
	model_loc = shader_program->find_uniform("model");
}

Camera::~Camera() {}

void Camera::rotate_yaw(double angle){
	yaw += angle;
	yaw = glm::mod(yaw, 2.0 * pi);
}

void Camera::rotate_pitch(double angle) {
	pitch += angle;
	pitch = glm::mod(pitch, 2.0 * pi);
}

void Camera::update_dim(GLsizei width, GLsizei height) {
	this->width = width;
	this->height = height;
	std::cout << "Resized " << width << " * " << height << std::endl;
}

void Camera::update_matrices(){
	proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
	view = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.5f), glm::vec3(1.0f, 3.0f, 1.0f)); // Debug and Test Purpose: should be static (identity Matrix)
	view = glm::rotate(view, (float)(yaw), -glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, (float)(pitch), -glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, input);
}


void Camera::load_matrices() {
	shader_program->setUniformMat4f(proj_loc, proj);
	shader_program->setUniformMat4f(view_loc, view);
	shader_program->setUniformMat4f(model_loc, model);
}