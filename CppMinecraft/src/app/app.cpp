#include "app.h"

#ifdef _DEBUG
#define _GL_DEBUG
#endif

namespace Application
{
    using std::make_shared;
    using std::make_unique;

    App::App(size_t width, size_t height, bool vsync, bool gl_debug, bool msaa)
        :shader_program(), width(width), height(height), vsync(vsync), window(nullptr),
        texture_manager(), camera(), player(), world(), hitray()
    {
        /* Initialize the library */
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW\n";
            throw std::runtime_error("Failed to initialize GLFW");
        }

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, "CMinecraft", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            std::cerr << "Failed to create a GLFW window\n";
            throw std::runtime_error("Failed to create a GLFW window");
        }

        /* Set events callbacks */
        glfwSetFramebufferSizeCallback(window, on_resize);
        glfwSetMouseButtonCallback(window, on_mouse_press);
        glfwSetKeyCallback(window, on_key_update);
        glfwSetCursorPosCallback(window, on_cursor_move);
        


        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        glfwSwapInterval(vsync ? 1 : 0); // Set to 1 for Vsync, reduces overall electricity, cpu and gpu usage

        /* Initialize glew */
        GLenum err = glewInit(); 
        if (err != GLEW_OK) {
            std::cerr << "Error initializing GLEW: " << glewGetErrorString(err) << '\n';
            throw std::runtime_error("Error initializing GLEW");
        }

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';

        if (gl_debug)
        {
            /* Enable Debug output */
            std::cout << "Enabled OpenGL debugging\n";
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(GLDebugMsgCallback, nullptr);
        }

        if (msaa)
        {
            std::cout << "Enabled multisample antialiasing, expect low performance\n";
            glEnable(GL_MULTISAMPLE);
            glfwWindowHint(GLFW_SAMPLES, 4);
        }
    }
    
    void App::init()
    {
        /* Initialize shaders */
        std::cout << "Compiling and building core shaders\n";
        shader_program = new AbstractGL::ShaderProgram;
        {
            AbstractGL::Shader vs("res/shaders/vertex_shader.glsl", GL_VERTEX_SHADER),
                fs("res/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
            shader_program->bindShader(std::move(vs));
            shader_program->bindShader(std::move(fs));
        }
        shader_program->compile();
        shader_program->use();

        /* Creating the texture manager */
        std::cout << "Loading textures\n";
        texture_manager = make_shared<Texturing::TextureManager>(16, 16, shader_program);

        /* Create the World */
        std::cout << "Loading and generating World\n";
        world = new World::World(texture_manager);

        /* Create the player, camera */
        std::cout << "Initializing Camera\n";
        player = new Entity::Player(glm::vec3(16, 70, 16), 5);
        camera = new Scene::Camera(player, shader_program, 852, 480);

        hitray = new Entity::PlayerHitray(world);

        /* Link some elements for the callbacks */
        Application::link_elements(player, camera, world, hitray);
    }

    App::~App() noexcept
    {
        delete world;
        delete hitray;
        delete player;
        delete camera;
        delete shader_program;
    }

    inline void App::update(float delta_time)
    {
        /* Update the Camera */
        camera->update(delta_time);
        draw();
    }

    inline void App::draw()
    {
        /* Clear some stuff here*/
        glClearColor(0.4f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
#ifndef _DEBUG
        glEnable(GL_CULL_FACE);
#endif
        /* Draw Calls */
        world->render(); // Render the world
    }

    void App::run()
    {
        float current_time;
        float prev_time = glfwGetTime();
        float delta_time;
        while (!glfwWindowShouldClose(window))
        {
            /* FPS stuff*/
            current_time = glfwGetTime();
            delta_time = current_time - prev_time;
            // std::cout << (int)(1 / delta_time) << " FPS" << std::endl;
            // Event system I guess ?
            // camera->rotate_yaw(glm::radians((double)(2 * ((int)current_time % 2) - 1)/5.0));
            prev_time = current_time;

            /* Update the Application*/
            update(delta_time);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        }
        /* Terminate the Application*/
        glfwTerminate();
    }
}