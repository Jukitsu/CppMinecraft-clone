#pragma once
#include "OpenGL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "entity/player/player.h"
#include "abstractgl/shader.h"

namespace Scene
{
	class Camera 
	{
		Entity::Player* player;
		glm::mat4 proj, view, model, mvp;
		glm::vec3 input;
		GLubyte mvp_loc;
		AbstractGL::ShaderProgram* shader_program;
	public:
		size_t width, height;

		Camera(Entity::Player* player,
			AbstractGL::ShaderProgram* shader_program, GLsizei width, GLsizei height)
			:player(player), shader_program(shader_program), input(0, 0, 0),
			proj(1.0f), view(1.0f), model(1.0f), width(width),
			height(height), mvp_loc()
		{
			proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
			view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
			model = glm::mat4(1.0f);
			mvp_loc = shader_program->findUniform("mvp");
		}
		~Camera()
		{

		}
		void poll_input(const glm::vec3& tvec)
		{
			input += tvec;
		}
		void reset_input()
		{
			input = glm::vec3(0, 0, 0);
		}
		void update_dim(GLsizei width, GLsizei height)
		{
			this->width = width;
			this->height = height;
			proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
			std::cout << "Resized " << width << " * " << height << '\n';
		}
		void update(float delta_time)
		{
			player->updatePos(input, delta_time);
			update_matrices();
			load_matrices();
		}
	private:
		void update_matrices()
		{
			view = glm::mat4(1.0f);
			model = glm::mat4(1.0f);
			view = glm::rotate(view, -player->getPitch(), -glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::rotate(view, -(player->getYaw() - pi / 2), -glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::translate(view, -player->getPos());
			mvp = proj * view * model;
		}
		void load_matrices()
		{
			shader_program->setUniformMat4f(mvp_loc, mvp);
		}
	};
}
