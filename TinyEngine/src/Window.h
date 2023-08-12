#pragma once
#include <string>
#include <GLFW/glfw3.h>

namespace TE
{
    struct WindowData
    {
        std::string Title;
        int Width;
        int Height;
    };

    class Window
    {
    public:
        Window(const WindowData& windowData);
        Window(const char* title, int width, int height);
        ~Window();
        void OnUpdate();
        bool ShouldClose();
        GLFWwindow* GlfwWindow;
    };
}
