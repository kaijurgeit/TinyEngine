#pragma once
#include <string>
#include <GLFW/glfw3.h>

#include "Core.h"

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
