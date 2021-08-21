#pragma once
#include "OpenGL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "entity/player.h"
#include "abstractgl/shader.h"

namespace Scene
{
	class Camera 
	{
	public:
		Entity::Player* player;
		glm::mat4 proj, view, model;
		glm::vec3 input;
		GLubyte proj_loc, view_loc, model_loc;
		GLsizei width, height;
		AbstractGL::ShaderProgram* shader_program;
		Camera(Entity::Player* player,
			AbstractGL::ShaderProgram* shader_program, GLsizei width, GLsizei height);
		~Camera();
		void poll_input(const glm::vec3& tvec);
		void reset_input();
		void update_dim(GLsizei width, GLsizei height);
		void update(float delta_time);
	private:
		inline void update_matrices();
		inline void load_matrices();
	};
}
