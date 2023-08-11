#include "Window.h"

#include <iostream>

#include "Core.h"



namespace  TE
{    
    Window::Window(const WindowData& windowData)
    {
        Window(windowData.Title.c_str(), windowData.Width,windowData.Height);
    }

    Window::Window(const char* title, int width, int height)
    {
        int success = glfwInit();
        glfwSetErrorCallback([](int error, const char* msg)
        {
            std::cerr << printf("GLFW Error %i: {%s}", error, msg) << std::endl;
        });
        TE_ASSERT(success, "Could not initialize GLFW!");

        // OpenGL 4.3 - specify version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        void APIENTRY glDebugOutput(
            GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message,
            const void *userParam);
#endif
    
        GLFWwindow* GlfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
        if (GlfwWindow == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
    
        glfwSetInputMode(GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);        
        glfwMakeContextCurrent(GlfwWindow);
    }

    void Window::OnUpdate()
    {
        glfwSwapBuffers(GlfwWindow);
        glfwPollEvents();
    }
}

