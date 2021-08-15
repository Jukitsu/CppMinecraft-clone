#include "Camera.h"


const double pi = glm::pi<double>();



Camera::Camera(ShaderProgram *shader_program, GLsizei width, GLsizei height)
	:shader_program(shader_program), input(0, 0, 0), position(0.0f, 0.0f, -3.0f),
	yaw(pi/2), pitch(0.0),
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

inline void Camera::rotate_yaw(double angle){
	yaw = glm::mod(yaw + angle, 2.0 * pi);
}

inline void Camera::rotate_pitch(double angle) {
	pitch = std::max(-pi / 2, std::min(pi / 2, pitch + angle));
}

void Camera::update_dim(GLsizei width, GLsizei height) {
	this->width = width;
	this->height = height;
	std::cout << "Resized " << width << " * " << height << '\n';
}

void Camera::update_pos(double delta_time) {
	int speed = 7;
	float multiplier = speed * (float)delta_time;
	position.y += input.y * multiplier;
	if (input.x || input.z) {
		double angle;
		angle = yaw + std::atan2(input.z, input.x) - pi/2;
		position.x += glm::cos(angle) * multiplier;
		position.z += glm::sin(angle) * multiplier;
	}
}

void Camera::update_matrices(){
	proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
	view = glm::mat4(1.0f);
	model = glm::mat4(1.0f); // Debug and Test Purpose: should be static (identity Matrix)
	view = glm::rotate(view, (float)(-(pitch)), -glm::vec3(1.0f, 0.0f, 0.0f));;
	view = glm::rotate(view, (float)(-(yaw - pi/2)), -glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::translate(view, position);
}

inline void Camera::poll_input(const glm::vec3 &tvec) {
	input += tvec;
}

inline void Camera::reset_input() {
	input = glm::vec3(0, 0, 0);
}


inline void Camera::load_matrices() {
	shader_program->setUniformMat4f(proj_loc, proj);
	shader_program->setUniformMat4f(view_loc, view);
	shader_program->setUniformMat4f(model_loc, model);
}

