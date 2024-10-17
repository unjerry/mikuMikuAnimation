#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <core/gmWindow.h>

void processInput(GLFWwindow *window);

// settings

int main()
{
    std::cout << "Hello Opengl" << std::endl;

    size_t windowNum = 20;
    gmWindow::gmWindow window[windowNum];
    bool shallClose = false;

    // render loop
    // -----------
    while (true)
    {
        if (shallClose)
        {
            break;
        }
        for (size_t i = 0; i < windowNum; i++)
        {
            if (glfwWindowShouldClose(window[i].getWindow()))
            {
                shallClose = true;
                break;
            }
            glfwMakeContextCurrent(window[i].getWindow());
            // input
            // -----
            processInput(window[i].getWindow());
            // render
            // ------
            window[i].getGl()->ClearColor(0.2f, 0.3f, 0.3f * i, 1.0f);
            window[i].getGl()->Clear(GL_COLOR_BUFFER_BIT);
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window[i].getWindow());
            glfwPollEvents();
        }
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
