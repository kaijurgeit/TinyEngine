#pragma once
#include <memory>
#include <string>
#include <glad/glad.h>
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
        void OnUpdate();
        GLFWwindow* GlfwWindow;
    };
}
