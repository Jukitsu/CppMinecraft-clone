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

#define default_tps 60.0

namespace Game {
    Camera *camera;
    ShaderProgram *shader_program;
    Renderer *mainrenderer;
};




// Filepath to the shaders
std::string vertexShaderFilepath = "res/shaders/vertex_shader.glsl"; 
std::string fragmentShaderFilepath = "res/shaders/fragment_shader.glsl";

void on_resize(GLFWwindow *window, GLsizei width, GLsizei height) {
    Game::camera->update_dim(width, height);
    glViewport(0, 0, width, height);
}




void draw(GLFWwindow *window, Renderer *renderer) {
    /* Render here */
    glCall (glClearColor(0.2f, 0.5f, 1.0f, 1.0f));
    glCall (glClear(GL_COLOR_BUFFER_BIT));
    glCall (glClear(GL_DEPTH_BUFFER_BIT));
    glCall (glEnable(GL_DEPTH_TEST));

    renderer->draw();
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}




int main(int argv, char *argc[])
{
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

    glfwSetFramebufferSizeCallback(window, on_resize);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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
    ShaderProgram shader_program = createShaderProgram(VertexShader, FragmentShader);
    VertexShader.clear();
    FragmentShader.clear();
    shader_program.use();

    // Loading and Managing Textures

    TextureManager* texture_manager = new TextureManager(16, 16, &shader_program);
    texture_manager->add_texture("res/textures/cobblestone.png", 0);
    texture_manager->generate_mipmaps();
    texture_manager->activate();

    // Buffering Data to the Graphics card

    mainrenderer->sendData(cube_vertex_pos, 72, 3, cube_indices, 36, 0);
    mainrenderer->sendData(cube_tex_coords, 72, 3, cube_indices, 36, 1);
    
    // Setting Camera 
    
    Camera *camera = new Camera(&shader_program, 852, 480);
    
    // Setting uniforms (debug testing)


    shader_program.setUniform4f(shader_program.find_uniform("lighting"), 1.0f, 1.0f, 1.0f, 1.0f);
    shader_program.setUniform4f(shader_program.find_uniform("shading"), 1.0f, 1.0f, 1.0f, 1.0f);
    shader_program.setUniform4f(shader_program.find_uniform("overlay"), 0.0f, 0.0f, 0.0f, 0.0f);

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

        if (current_time - prev_time >= 1 / default_tps || true) {
            // Event system I guess ?
            // Example: camera->rotate_yaw(glm::radians((double)(2 * ((int)current_time % 2) - 1)/5.0));
            prev_time = current_time;
        }

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

