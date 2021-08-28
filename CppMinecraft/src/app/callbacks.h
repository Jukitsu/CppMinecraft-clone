#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include <iostream>

#include "entity/player.h"
#include "scene/camera.h"
#include "world/world.h"




namespace Application
{
    void APIENTRY GLDebugMsgCallback(GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length,
        const GLchar* msg, const void* data);

    void link_elements(Entity::Player* player, Scene::Camera* camera, World::World* world);
    void on_mouse_press(GLFWwindow* window, int button, int action, int mods);
    void on_resize(GLFWwindow* window, GLsizei width, GLsizei height);
    void on_cursor_move(GLFWwindow* window, double xpos, double ypos);
    void on_key_update(GLFWwindow* window, int key, int scancode, int action, int mods);
}
