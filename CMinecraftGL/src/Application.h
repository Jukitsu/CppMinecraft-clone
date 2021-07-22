#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <exception>
#include "renderer/gl/vbo.h"
#include "renderer/gl/ibo.h"
#include "renderer/gl/vao.h"
#include "renderer/gl/shader.h"
#include "util/glm/glm.hpp"
#include "util/glm/gtc/matrix_transform.hpp"
#include "renderer/Renderer.h"
#include "player/Camera.h"
#include "blocks/models/cube.h"
#include "texture/texture_manager.h"



static void on_resize(GLFWwindow* window, GLsizei width, GLsizei height);
static void on_mouse_press(GLFWwindow* window, int button, int action, int mods);
static void on_cursor_move(GLFWwindow* window, double xpos, double ypos);
static void on_key_update(GLFWwindow* window, int key, int scancode, int action, int mods);

class Application {
private:
    GLFWwindow *window;
    ShaderProgram shader_program;
    TextureManager texture_manager;
    Renderer mainrenderer;
    Camera camera;
    GLsizei width, height;
    bool vsync;
    double delta_time, prev_time, current_time;
public:
    Application(GLsizei width, GLsizei height, bool vsync);
    ~Application();
    void init();
    void draw();
    void run();  
    int stop();
};
