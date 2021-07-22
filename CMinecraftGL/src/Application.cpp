#include "Application.h"

namespace AppElements {
    Camera* camera;
    ShaderProgram* shader_program;
    Renderer* mainrenderer;
    bool mouse_captured;
    double last_x_pos, last_y_pos;
    double sensitivity = 0.004;
};

static void on_mouse_press(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS && glfwGetWindowAttrib(window, GLFW_HOVERED)) {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (!AppElements::mouse_captured) {
                AppElements::mouse_captured = true;
                glfwSetCursorPos(window, (double)AppElements::camera->width / 2, 
                    (double)AppElements::camera->height / 2);
                AppElements::last_x_pos = (double)AppElements::camera->width / 2;
                AppElements::last_y_pos = (double)AppElements::camera->height / 2;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
    }
}

static void on_resize(GLFWwindow* window, GLsizei width, GLsizei height) {
    AppElements::camera->update_dim(width, height);
    glViewport(0, 0, width, height);
}

static void on_cursor_move(GLFWwindow* window, double xpos, double ypos) {
    if (!AppElements::mouse_captured) {
        return; // Short circuit
    }
    double dx, dy;
    dx = AppElements::last_x_pos - xpos,
        dy = AppElements::last_y_pos - ypos;
    AppElements::camera->rotate_yaw(-dx * AppElements::sensitivity);
    AppElements::camera->rotate_pitch(-dy * AppElements::sensitivity);
    AppElements::last_x_pos = xpos;
    AppElements::last_y_pos = ypos;
}

static void on_key_update(GLFWwindow* window, int key, int scancode, int action, int mods) {
    int dx, dy, dz;
    dx = 0; dy = 0; dz = 0;
    if (AppElements::mouse_captured) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_ESCAPE:
                AppElements::mouse_captured = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                AppElements::camera->reset_input();
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
    AppElements::camera->poll_input(glm::vec3(dx, dy, dz));
}

Application::Application(GLsizei width, GLsizei height, bool vsync)
    :mainrenderer(), texture_manager(0, 0, nullptr),
    camera(nullptr, 0, 0), width(width), height(height),
    delta_time(), current_time(), prev_time(), vsync(),
    window(nullptr)
{
    /* Initialize the library */
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize library");

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "CMinecraft", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window";
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    /* Set events callbacks*/
    AppElements::mouse_captured = false;
    glfwSetFramebufferSizeCallback(window, on_resize);
    glfwSetMouseButtonCallback(window, on_mouse_press);
    glfwSetKeyCallback(window, on_key_update);
    glfwSetCursorPosCallback(window, on_cursor_move);




    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval((int)vsync); // Set to 1 for Vsync, reduces overall electricity, cpu and gpu usage

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;


    /* Setting up a mainrenderer, its buffersand vertex array */
    mainrenderer.init();

    /* Creating Shaders */
    Shader VertexShader = Shader("res/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader FragmentShader = Shader("res/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    shader_program.bind_shader(VertexShader);
    shader_program.bind_shader(FragmentShader);
    shader_program.compile();
    shader_program.use();

    /* Loading and Managing Textures */
    texture_manager = TextureManager(16, 16, &shader_program);
    texture_manager.add_texture("res/textures/stone.png", 0);
    texture_manager.generate_mipmaps();
    texture_manager.activate();

    /* Buffering Data to the GPU */
    mainrenderer.sendData(cube_vertex_data, 168, 3, cube_indices, 36, 0);
    mainrenderer.link_attrib(0, 3, GL_FLOAT, 7 * sizeof(GLfloat), 0);
    mainrenderer.link_attrib(1, 3, GL_FLOAT, 7 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    mainrenderer.link_attrib(2, 1, GL_FLOAT, 7 * sizeof(GLfloat), 6 * sizeof(GLfloat));
    mainrenderer.clear();

    /* Setting Camera */
    camera = Camera(&shader_program, 852, 480);


    // FPS ig ?

    prev_time = glfwGetTime();

    /* Link important stuff so we can access it elsewhere (not the best way to do it ngl) */
    AppElements::camera = &camera;
    AppElements::shader_program = &shader_program;
    AppElements::mainrenderer = &mainrenderer;
}

Application::~Application() {
    glfwTerminate();
}

void Application::draw() {
    glCall(glClearColor(0.2f, 0.5f, 1.0f, 1.0f));
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glCall(glEnable(GL_DEPTH_TEST));
    mainrenderer.draw();
}

int Application::stop() {
    glfwTerminate();
    return 0;
}

void Application::run() {
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        current_time = glfwGetTime();

        // Tick 

        delta_time = current_time - prev_time;
        std::cout << (int)(1 / delta_time) << " FPS" << std::endl;
        // Event system I guess ?
        // camera->rotate_yaw(glm::radians((double)(2 * ((int)current_time % 2) - 1)/5.0));
        prev_time = current_time;

        camera.update_pos(delta_time);

        /*3D stuff*/

        camera.update_matrices();
        camera.load_matrices();

        /*Bind the VAO and IBOs*/
        mainrenderer.bind_all();

        /* Draw Call*/
        draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}