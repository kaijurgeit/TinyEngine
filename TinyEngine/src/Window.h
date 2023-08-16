#pragma once
#include <string>

#include "Core.h"
#include <GLFW/glfw3.h>

namespace TE
{
    
    struct WindowData
    {
        std::string Title;
        int Width;
        int Height;
    };

    class TE_API Window
    {
    public:
        Window(const WindowData& windowData);
        void InitWindow(const char* title, int width, int height);
        void InitCallbacks();
        Window(const char* title, int width, int height);
        ~Window();
        void OnUpdate();
        bool ShouldClose();
        GLFWwindow* GlfwWindow;

        std::string Title;
        int Width;
        int Height;
    };
}
