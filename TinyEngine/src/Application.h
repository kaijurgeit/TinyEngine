#pragma once

#include "Core.h"

class Event;

namespace TE
{
    class Window;
    class Renderer;
    class Camera;    
    
    // Abstract Class
    class TE_API Application
    {
    public:        
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event& event);
        
        static Application& Get() { return *instance; }
        static Window& GetWindow() { return *Get().window.get(); }
        static Renderer& GetRenderer() { return *Get().renderer.get(); }
        static Camera& GetCamera() { return *Get().camera.get(); }
        
    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Camera> camera;

        static Application* instance;
    };
    
    Application* CreateApplication();
}
