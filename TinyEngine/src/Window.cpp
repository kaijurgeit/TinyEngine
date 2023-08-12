#include "Window.h"

#include <iostream>



namespace  TE
{    
    Window::Window(const WindowData& windowData)
    {
        Window(windowData.Title.c_str(), windowData.Width,windowData.Height);
    }

    Window::Window(const char* title, int width, int height)
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

        constexpr int SCR_WIDTH = 800;
        constexpr int SCR_HEIGHT = 600;
        
        // glfw window creation
        // --------------------
        GlfwWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (GlfwWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(GlfwWindow);
    }

    Window::~Window()
    {
		glfwDestroyWindow(GlfwWindow);
        glfwTerminate();
    }

    void Window::OnUpdate()
    {
        glfwSwapBuffers(GlfwWindow);
        glfwPollEvents();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(GlfwWindow);
    }
}

