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

        std::string GetTitle() const { return title; }
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        
        void SetEventCallback(const std::function<void(Event&)>& eventCallback) { this->eventCallback = eventCallback; }
        
        GLFWwindow* glfwWindow;

    private:
        std::string title;
        int width;
        int height;

        std::function<void(Event&)> eventCallback;

        MouseData mouse;
    };
}
