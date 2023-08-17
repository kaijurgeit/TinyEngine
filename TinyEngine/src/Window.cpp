#include "Window.h"
#include <iostream>

#include <glad/glad.h>

namespace  TE
{   
    Window::Window(const char* title, int width, int height)
        : Title(title), Width(width), Height(height)
    {
        InitWindow(title, width, height);
        InitCallbacks();
    }

    Window::~Window()
    {
        glfwDestroyWindow(GlfwWindow);
        glfwTerminate();
    }

    void Window::InitWindow(const char* title, int width, int height)
    {
        // OpenGL 4.3
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create GLFW window
        GlfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
        if (GlfwWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(GlfwWindow);
    }

    void Window::InitCallbacks()
    {
        glfwSetWindowUserPointer(GlfwWindow, this);
        
        glfwSetFramebufferSizeCallback(GlfwWindow, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });

        glfwSetKeyCallback(GlfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            
            // switch(action)
            // {
            // case GLFW_PRESS:
            // }
        });
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

