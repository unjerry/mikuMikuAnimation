#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <core/gmWindow.h>

void processInput(GLFWwindow *window);

// settings

int main()
{
    std::cout << "Hello Opengl" << std::endl;

    gmWindow::gmWindow window;
    gmWindow::gmWindow window2;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window.getWindow()) && !glfwWindowShouldClose(window2.getWindow()))
    {
        glfwMakeContextCurrent(window.getWindow());
        // input
        // -----
        processInput(window.getWindow());

        // render
        // ------
        window.getGl()->ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        window.getGl()->Clear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();

        glfwMakeContextCurrent(window2.getWindow());
        // input
        // -----
        processInput(window2.getWindow());

        // render
        // ------
        window2.getGl()->ClearColor(0.2f, 0.3f, 0.9f, 1.0f);
        window2.getGl()->Clear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window2.getWindow());
        glfwPollEvents();
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
