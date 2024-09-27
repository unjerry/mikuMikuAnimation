#ifndef GMWINDOW_H
#define GMWINDOW_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace gmWindow
{
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

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
        GladGLContext *gl;

    public:
        gmWindow(const gmWindowSpecification &spec = gmWindowSpecification());
        ~gmWindow();
        GLFWwindow *getWindow();
        GladGLContext *getGl();
    };
    GLFWwindow *gmWindow::getWindow()
    {
        return window;
    }
    GladGLContext *gmWindow::getGl()
    {
        return gl;
    }
    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glfwMakeContextCurrent(window);
        GladGLContext *gl = (GladGLContext *)calloc(1, sizeof(GladGLContext));
        if (!gl)
        {
            throw std::invalid_argument("Failed to create context");
        }

        int version = gladLoadGLContext(gl, glfwGetProcAddress);
        std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
        gl->Viewport(0, 0, width, height);
        free(gl);
    }
    gmWindow::gmWindow(const gmWindowSpecification &spec) : mSpecification(spec)
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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
        gl = (GladGLContext *)calloc(1, sizeof(GladGLContext));
        if (!gl)
        {
            throw std::invalid_argument("Failed to create context");
        }

        int version = gladLoadGLContext(gl, glfwGetProcAddress);
        std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        // if ()
        // {
        //     std::cout << "Failed to initialize GLAD" << std::endl;
        //     throw std::invalid_argument("Failed to initialize GLAD");
        // }
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    gmWindow::~gmWindow()
    {
        free(gl);
    }

} // namespace gmWindow

#endif
