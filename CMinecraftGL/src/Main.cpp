#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
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


#define sensitivity 0.004




namespace Game {
    Camera *camera;
    ShaderProgram *shader_program;
    Renderer *mainrenderer;
    bool mouse_captured;
    double last_x_pos, last_y_pos;
};





// Filepath to the shaders
std::string vertexShaderFilepath = "res/shaders/vertex_shader.glsl"; 
std::string fragmentShaderFilepath = "res/shaders/fragment_shader.glsl";

static void on_mouse_press(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS && glfwGetWindowAttrib(window, GLFW_HOVERED)) {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (!Game::mouse_captured) {
                Game::mouse_captured = true;
                glfwSetCursorPos(window, (double)Game::camera->width / 2, (double)Game::camera->height / 2);
                Game::last_x_pos = (double)Game::camera->width / 2;
                Game::last_y_pos = (double)Game::camera->height / 2;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
    }    
}

static void on_resize(GLFWwindow *window, GLsizei width, GLsizei height) {
    Game::camera->update_dim(width, height);
    glViewport(0, 0, width, height);
}

static void on_cursor_move(GLFWwindow* window, double xpos, double ypos) {
    if (!Game::mouse_captured) {
        return; // Short circuit
    }
    double dx, dy;
    dx = Game::last_x_pos - xpos,
    dy = Game::last_y_pos - ypos;
    Game::camera->rotate_yaw(-dx * sensitivity);
    Game::camera->rotate_pitch(-dy * sensitivity);
    Game::last_x_pos = xpos;
    Game::last_y_pos = ypos;
}

static void on_key_update(GLFWwindow* window, int key, int scancode, int action, int mods) {
    int dx, dy, dz;
    dx = 0; dy = 0; dz = 0;
    if (Game::mouse_captured) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_ESCAPE:
                Game::mouse_captured = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                Game::camera->reset_input();
                break;
            case GLFW_KEY_W:
                dz = 1;
                break;
            case GLFW_KEY_S:
                dz = -1;
                break;
            case GLFW_KEY_A:
                dx = 1;
                break;
            case GLFW_KEY_D:
                dx = -1;
                break;
            case GLFW_KEY_SPACE:
                dy = -1;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                dy = 1;
                break;
            }
        }
        else if (action == GLFW_RELEASE) {
            switch (key) {
            case GLFW_KEY_W:
                dz = -1;
                break;
            case GLFW_KEY_S:
                dz = 1;
                break;
            case GLFW_KEY_A:
                dx = -1;
                break;
            case GLFW_KEY_D:
                dx = 1;
                break;
            case GLFW_KEY_SPACE:
                dy = 1;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                dy = -1;
                break;
            }
        }
    }
    Game::camera->poll_input(glm::vec3(dx, dy, dz));
}

static void draw(GLFWwindow *window, Renderer *renderer) {
    /* Render here */
    glCall (glClearColor(0.2f, 0.5f, 1.0f, 1.0f));
    glCall (glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glCall (glEnable(GL_DEPTH_TEST));
    glCall (glEnable(GL_CULL_FACE));

    renderer->draw();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}




int main(int argv, char *argc[])
{
    Game::mouse_captured = false;
    GLFWwindow *window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(852, 480, "CMinecraft", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Set events callbacks*/
    double delta_time;
    glfwSetFramebufferSizeCallback(window, on_resize);
    glfwSetMouseButtonCallback(window, on_mouse_press);
    glfwSetKeyCallback(window, on_key_update);
    glfwSetCursorPosCallback(window, on_cursor_move);
    



    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Set to 1 for Vsync, reduces overall electricity, cpu and gpu usage

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
    

    // Setting up a mainrenderer, its buffers and vertex array

    Renderer *mainrenderer = new Renderer();
    mainrenderer->init();

    
    // Creating Shaders

    Shader VertexShader = Shader("res/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader FragmentShader = Shader("res/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shader_program;
    shader_program.bindShader(VertexShader);
    shader_program.bindShader(FragmentShader);
    shader_program.compileProgram();
    VertexShader.clear();
    FragmentShader.clear();
    shader_program.use();

    // Loading and Managing Textures

    TextureManager *texture_manager = new TextureManager(16, 16, &shader_program);
    texture_manager->add_texture("res/textures/stone.png", 0);
    texture_manager->generate_mipmaps();
    texture_manager->activate();

    // Buffering Data to the Graphics card

    mainrenderer->sendData(cube_vertex_data, 168, 3, cube_indices, 36, 0);
    mainrenderer->link_attrib(0, 3, GL_FLOAT, 7 * sizeof(GLfloat), 0);
    mainrenderer->link_attrib(1, 3, GL_FLOAT, 7 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    mainrenderer->link_attrib(2, 1, GL_FLOAT, 7 * sizeof(GLfloat), 6 * sizeof(GLfloat));

    // Setting Camera 
    
    Camera *camera = new Camera(&shader_program, 852, 480);
   

    // FPS ig ?

    double prev_time = glfwGetTime();
    double current_time;

    // Link important stuff so we can access it elsewhere (not the best way to do it ngl)

    Game::camera = camera;
    Game::shader_program = &shader_program;
    Game::mainrenderer = mainrenderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        current_time = glfwGetTime();

        // Tick

        delta_time = current_time - prev_time;
        // std::cout << 1/delta_time << " FPS" << std::endl;
        // Event system I guess ?
        // camera->rotate_yaw(glm::radians((double)(2 * ((int)current_time % 2) - 1)/5.0));
        prev_time = current_time;

        camera->update_pos(delta_time);

        // 3D stuff

        camera->update_matrices();
        camera->load_matrices();

        // Bind the VAO and IBOs
        mainrenderer->bind_all();

        // Draw stuff
        draw(window, mainrenderer);
    }
    // Deallocate all
    shader_program.delete_program();
    delete mainrenderer;
    delete camera;
    delete texture_manager;
    glfwTerminate();
    return 0;
}

