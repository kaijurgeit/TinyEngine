#pragma once

#include "Core.h"

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
        
    private:
        std::unique_ptr<Window> Window;
        std::unique_ptr<Renderer> Renderer;
    };
    
    Application* CreateApplication();
}
