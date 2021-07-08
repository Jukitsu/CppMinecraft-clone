#include "Camera.h"


const double pi = glm::pi<double>();

Camera::Camera(ShaderProgram *shader_program, GLsizei width, GLsizei height)
	:shader_program(shader_program), input(0, 0, -1), 
	position(0, 0, 0), yaw(0.0), pitch(0.0),
	proj(1.0f), view(1.0f), model(1.0f), mvp(1.0f), width(width),
	height(height)
{
	proj = glm::perspective(glm::radians(70.0f), (float)(width / height), 0.1f, 500.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::mat4(1.0f);
}

Camera::~Camera() {}

void Camera::rotate_yaw(double angle){
	yaw += angle;
}

void Camera::rotate_pitch(double angle) {
	pitch += angle;
}

void Camera::update_matrices(){
	proj = glm::perspective(glm::radians(70.0f), (float)(width / height), 0.1f, 500.0f);
	view = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	view = glm::rotate(view, (float)(yaw), -glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, (float)(pitch), -glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, input);
	mvp = proj * view * model;
}


void Camera::load_matrices() {
	shader_program->setUniformMat4f("matrix", mvp);
}