#pragma once

#include "Core.h"

class Event;

namespace TE
{
    class Window;
    class Renderer;
    
    // Abstract Class
    class TE_API Application
    {
    public:        
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event& event);
        
    private:
        std::unique_ptr<Window> Window;
        std::unique_ptr<Renderer> Renderer;
    };
    
    Application* CreateApplication();
}
