#define GLEW_STATIC
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
#include "util/mth.h"
#include "player/Camera.h"

#define default_tps 60.0


GLfloat vertices[12] = { // Vertex Positions
    -0.5, 0.5, 0.0,
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.5, 0.5, 0.0
};


GLuint indices[6] = { // Indices 
    0, 1, 2,
    0, 2, 3
};

// Filepath to the shaders
std::string vertexShaderFilepath = "res/shaders/vertex_shader.glsl"; 
std::string fragmentShaderFilepath = "res/shaders/fragment_shader.glsl";

void on_resize(GLFWwindow *window, GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
}




void draw(GLFWwindow *window, Renderer *renderer) {
    /* Render here */
    renderer->draw();
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}




int main(void)
{
    GLFWwindow* window;

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

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Setting up a mainrenderer, its buffers and vertex array

    Renderer *mainrenderer = new Renderer();
    mainrenderer->init();

    // Buffering Data to the Graphics card

    mainrenderer->sendData(vertices, 12, 3, indices, 6, 0);

    // 3D matrices, gonna abstract it so its useless rn

    glm::mat4 proj_matrix = glm::identity<glm::mat4>();
    glm::mat4 mv_matrix = glm::identity<glm::mat4>();
    glm::mat4 mvp_matrix = glm::identity<glm::mat4>();
    
    // Creating Shaders

    Shader VertexShader = Shader("res/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader FragmentShader = Shader("res/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shader_program = createShaderProgram(VertexShader, FragmentShader);
    VertexShader.clear();
    FragmentShader.clear();
    shader_program.use();
    
    // Setting Camera 
    
    Camera *camera = new Camera(&shader_program, 852, 480);
    
    // Setting uniforms (debug testing)

    shader_program.setUniform4f("color_on", 0.0f, 0.0f, 0.0f, 0.0f); // Uniform testing
    shader_program.setUniform4f("shading", 1.0f, 1.0f, 1.0f, 1.0f);
    shader_program.setUniform4f("overlay", 0.0f, 0.0f, 0.0f, 0.0f);

    // FPS ig ?

    double prev_time = glfwGetTime();
    double current_time;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Making the scene 3D, but doesnt work for now, uses identity matrix for now
        current_time = glfwGetTime();

        // Tick

        if (current_time - prev_time >= 1 / default_tps) {
            camera->rotate_yaw(glm::radians(1.0));
            prev_time = current_time;
        }
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
    glfwTerminate();
    return 0;
}

