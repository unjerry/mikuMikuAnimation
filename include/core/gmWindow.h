#ifndef GMWINDOW_H
#define GMWINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace gmWindow
{
    struct gmWindowSpecification
    {
        /* data */
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;
    };

    class gmWindow
    {
    private:
        /* data */
        gmWindowSpecification mSpecification;
        GLFWwindow *window;

    public:
        gmWindow(const gmWindowSpecification &spec = gmWindowSpecification());
        ~gmWindow();
        GLFWwindow *getWindow();
    };
    GLFWwindow *gmWindow::getWindow()
    {
        return window;
    }

    gmWindow::gmWindow(const gmWindowSpecification &spec) : mSpecification(spec)
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(mSpecification.SCR_WIDTH, mSpecification.SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::invalid_argument("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw std::invalid_argument("Failed to initialize GLAD");
        }
    }

    gmWindow::~gmWindow()
    {
    }

} // namespace gmWindow

#endif
