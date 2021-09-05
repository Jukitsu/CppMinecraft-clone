#pragma once
#include "OpenGL.h"

#include <iostream>
#include <exception>

#include "blocks/block_type.h"
#include "blocks/models/models.h"
#include "abstractgl/shader.h"
#include "renderer/renderer.h"
#include "renderer/mesh.h"
#include "renderer/geometry.h"
#include "texture/texture_manager.h"
#include "entity/player/player.h"
#include "scene/camera.h"
#include "world/world.h"
#include "callbacks.h"


namespace Application
{
	class App
	{
		AbstractGL::ShaderProgram* shader_program;
		Entity::Player* player;
		Entity::PlayerHitray* hitray;
		Scene::Camera* camera;
		std::shared_ptr<Texturing::TextureManager> texture_manager;
		World::World* world;
		GLFWwindow* window;
		size_t width, height;
		bool vsync;
	public:
		App(size_t width, size_t height, bool vsync, bool gl_debug, bool msaa);
		~App() noexcept;
		void init();
		inline void update(float delta_time);
		inline void draw();
		void run();
	};
}