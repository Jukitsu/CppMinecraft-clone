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





GLfloat vertices[12] = {
    -0.5, 0.5, 1.0,
    -0.5, -0.5, 1.0,
    0.5, -0.5, 1.0,
    0.5, 0.5, 1.0
};


GLuint indices[6] = {
    0, 1, 2,
    0, 2, 3
};

std::string vertexShaderFilepath = "res/shaders/vertex_shader.glsl";
std::string fragmentShaderFilepath = "res/shaders/fragment_shader.glsl";

void on_resize(GLFWwindow* window, GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
}




void draw(GLFWwindow* window, Renderer* renderer) {
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
    window = glfwCreateWindow(852, 480, "CMinecraft", NULL, NULL);
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

    if (false) {
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ibo;
        vao.init();
        vbo.init();
        ibo.init();
        vao.bind();
        vbo.sendData(vertices, 12 * sizeof(GLfloat), 3, 0);
        vbo.bind();
        ibo.sendIndices(indices, 6 * sizeof(GLfloat));
        ibo.bind();
    }

    Renderer* mainrenderer = new Renderer();
    mainrenderer->init();
    mainrenderer->sendData(vertices, 12, 3, indices, 6, 0);
    glm::mat4 proj_matrix;
    glm::mat4 mv_matrix;
    glm::mat4 mvp_matrix;
    Shader VertexShader = Shader("res/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader FragmentShader = Shader("res/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shader_program = createShaderProgram(VertexShader, FragmentShader);
    VertexShader.clear();
    FragmentShader.clear();
    shader_program.use();

    int location = shader_program.find_uniform("color");
    glCall (glUniform4f(location, 0.0f, 0.0f, 0.5f, 0.0f)); // Uniform testing


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (false) {
            proj_matrix = glm::perspective((GLfloat)90, (GLfloat)(852 / 480), (GLfloat)0.1, (GLfloat)500);
            mv_matrix = glm::mat4();
            glm::translate(mv_matrix, glm::vec3(0, 0, -1));
            glm::rotate(mv_matrix, (GLfloat)glm::radians(1.0), glm::vec3(0, 1, 0));
            mvp_matrix = mv_matrix * proj_matrix;

            shader_program.setUniformMat4f("matrix", mvp_matrix);
        }

        mainrenderer->bind_all();
        draw(window, mainrenderer);
    }
    shader_program.delete_program();
    delete mainrenderer;
    glfwTerminate();
    return 0;
}

