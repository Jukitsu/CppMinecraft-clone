#include "app.h"

namespace Application
{
    using std::make_shared;
    using std::make_unique;

    App::App(unsigned int width, unsigned int height, bool vsync)
        :shader_program(), width(width), height(height), vsync(vsync), window(nullptr),
        texture_manager()
    {
        /* Initialize the library */
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, "CMinecraft", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
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

        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Error: " << glewGetErrorString(err) << '\n';
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugMsgCallback, nullptr);

        std::cout << "OpenGL Version " << glGetString(GL_VERSION) << '\n';
    }
    
    void App::init()
    {
        shader_program = new AbstractGL::ShaderProgram;
        {
            AbstractGL::Shader vs("res/shaders/vertex_shader.glsl", GL_VERTEX_SHADER),
                fs("res/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
            shader_program->bindShader(std::move(vs));
            shader_program->bindShader(std::move(fs));
        }
        shader_program->compile();
        shader_program->use();
      
        player = new Entity::Player(glm::vec3(0.0, 0.0, -0.3));

        camera = new Scene::Camera(player, shader_program, 852, 480);
        
        texture_manager = make_shared<Texturing::TextureManager>(16, 16, shader_program);

        world = make_unique<World::World>(texture_manager);

        Application::link_player(player, camera);
    }

    App::~App() noexcept
    {
        delete shader_program;
        delete player;
        delete camera;
    }

    inline void App::update()
    {
        draw();
    }

    inline void App::draw()
    {
        glClearColor(0.25f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        world->render();
    }

    void App::run()
    {
        float current_time;
        float prev_time = glfwGetTime();
        float delta_time;
        while (!glfwWindowShouldClose(window))
        {

            current_time = glfwGetTime();

            // Tick 
            delta_time = current_time - prev_time;
            // std::cout << (int)(1 / delta_time) << " FPS" << std::endl;
            // Event system I guess ?
            // camera->rotate_yaw(glm::radians((double)(2 * ((int)current_time % 2) - 1)/5.0));
            prev_time = current_time;

            // camera.update_pos(delta_time);

            /*3D stuff*/

            camera->update(delta_time);

            /*Bind the VAO and IBOs*/
            // mainrenderer.bind_all();

            /* Draw Call*/
            update();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        }
        glfwTerminate();
    }
}