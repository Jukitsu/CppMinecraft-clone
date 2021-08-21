#include "camera.h"


namespace Scene
{
	using Entity::Player;
	using namespace AbstractGL;

	Camera::Camera(Player* player,
		ShaderProgram* shader_program, GLsizei width, GLsizei height)
		:player(player), shader_program(shader_program), input(0, 0, 0),
		proj(1.0f), view(1.0f), model(1.0f), width(width),
		height(height), proj_loc(), view_loc(), model_loc()
	{
		proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::mat4(1.0f);
		proj_loc = shader_program->findUniform("proj");
		view_loc = shader_program->findUniform("view");
		model_loc = shader_program->findUniform("model");
	}

	Camera::~Camera()
	{

	}

	void Camera::update_dim(GLsizei width, GLsizei height) {
		this->width = width;
		this->height = height;
		std::cout << "Resized " << width << " * " << height << '\n';
	}

	void Camera::poll_input(const glm::vec3& tvec) {
		input += tvec;
	}

	void Camera::reset_input() {
		input = glm::vec3(0, 0, 0);
	}

	void Camera::update(float delta_time)
	{
		player->updatePos(input, delta_time);
		update_matrices();
		load_matrices();
	}

	inline void Camera::update_matrices() {
		proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
		view = glm::mat4(1.0f);
		model = glm::mat4(1.0f); 
		view = glm::rotate(view, (float)(-(player->getPitch())), -glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, (float)(-(player->getYaw() - pi / 2)), -glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, player->getPos());
	}

	inline void Camera::load_matrices() {
		shader_program->setUniformMat4f(proj_loc, proj);
		shader_program->setUniformMat4f(view_loc, view);
		shader_program->setUniformMat4f(model_loc, model);
	}
}