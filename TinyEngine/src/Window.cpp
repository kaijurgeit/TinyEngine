﻿#include "Window.h"
#include <iostream>

#include <glad/glad.h>

#include "Application.h"
#include "Camera.h"
#include "Event.h"

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
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

        // Create GLFW window
        GlfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
        if (GlfwWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(GlfwWindow);
        glfwSetInputMode(GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Window::InitCallbacks()
    {
        glfwSetWindowUserPointer(GlfwWindow, this);
        
        glfwSetFramebufferSizeCallback(GlfwWindow, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });
        
        glfwSetCursorPosCallback(GlfwWindow, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            float xpos = static_cast<float>(xposIn);
            float ypos = static_cast<float>(yposIn);

            if (self.mouse.firstMouse)
            {
                self.mouse.lastX = xpos;
                self.mouse.lastY = ypos;
                self.mouse.firstMouse = false;
            }

            float xoffset = xpos - self.mouse.lastX;
            float yoffset = self.mouse.lastY - ypos; // reversed since y-coordinates go from bottom to top

            self.mouse.lastX = xpos;
            self.mouse.lastY = ypos;

            Application::GetCamera().ProcessMouseMovement(xoffset, yoffset);
        });

        glfwSetScrollCallback(GlfwWindow, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            Application::GetCamera().ProcessMouseScroll(static_cast<float>(yoffset));
        });

        glfwSetKeyCallback(GlfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            
            switch(action)
            {
                case GLFW_PRESS:
                {
                    InputEvent event(key, ETriggerEvent::Pressed);
                    self.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {   
                    InputEvent event(key, ETriggerEvent::Released);
                    self.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {   
                    InputEvent event(key, ETriggerEvent::Repeat);
                    self.EventCallback(event);
                    break;
                }
            }
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

