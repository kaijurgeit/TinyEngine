#pragma once
#include <functional>
#include <string>

#include <GLFW/glfw3.h>
#include "Core.h"
#include "Event.h"

namespace TE
{
    class TE_API Window
    {
    public:        
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

        std::function<void(Event&)> EventCallback;
    };
}
