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
        struct MouseData
        {
            float lastX = 400.f;
            float lastY = 300.f;
            bool firstMouse = true;
        };
    public:
        Window(const char* title, int width, int height);
        Window(const Window& other) = default;
        Window(Window&& other) noexcept = default;
        Window& operator=(const Window& other) = default;
        Window& operator=(Window&& other) noexcept = default;
        ~Window();

        void InitWindow(const char* title, int width, int height);
        void InitCallbacks();
        void OnUpdate();
        bool ShouldClose();

        std::string GetTitle() const { return Title; }
        int GetWidth() const { return Width; }
        int GetHeight() const { return Height; }
        
        void SetEventCallback(const std::function<void(Event&)>& eventCallback) { EventCallback = eventCallback; }
        
        GLFWwindow* GlfwWindow;

    private:
        std::string Title;
        int Width;
        int Height;

        std::function<void(Event&)> EventCallback;

        MouseData mouse;
    };
}
