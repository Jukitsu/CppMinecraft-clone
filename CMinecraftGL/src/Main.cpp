#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/gl/vbo.h"
#include "renderer/gl/ibo.h"
#include "renderer/gl/vao.h"
#include "renderer/gl/shader.h"



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

void on_resize(GLFWwindow* window, GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
}




void draw(GLFWwindow* window) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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

    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.genVertexAttrib(0, 3);
    IndexBuffer ibo(indices, sizeof(indices));
    Shader VertexShader = Shader("res/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader FragmentShader = Shader("res/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shader_program = createShaderProgram(VertexShader, FragmentShader);
    VertexShader.clear();
    FragmentShader.clear();
    glUseProgram(shader_program.id);

    int location = glGetUniformLocation(shader_program.id, "color");
    glUniform4f(location, 0.0f, 0.0f, 0.0f, 0.0f); // Uniform testing


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        vao.bind();
        draw(window);
    }

    glDeleteProgram(shader_program.id);
    glfwTerminate();
    return 0;
}

