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
#include "entity/player.h"
#include "scene/camera.h"
#include "callbacks.h"

namespace Application
{
	class App
	{
		Rendering::Mesh mesh;
		Rendering::Renderer* renderer;
		AbstractGL::ShaderProgram* shader_program;
		Texturing::TextureManager* texture_manager;
		Entity::Player* player;
		Scene::Camera* camera;
		Blocks::Models::BlockModels models;
		std::vector<Blocks::BlockType> block_types;
		GLFWwindow* window;
		unsigned int width, height;
		bool vsync;
	public:
		App(unsigned int width, unsigned int height, bool vsync);
		~App() noexcept;
		void init();
		inline void update();
		inline void draw();
		void run();
	};
}