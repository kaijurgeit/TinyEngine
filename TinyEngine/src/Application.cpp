#include "Application.h"

#include "Renderer.h"
#include "Window.h"

namespace TE
{
    Application::Application()    
    {
        Window = std::make_unique<TE::Window>("TinyEngine App", 800, 600);
        Renderer = std::make_unique<TE::Renderer>();
    }
    
    Application::~Application()
    {
    }
    
    void Application::Run()
    {   
        while (true)
        {
            Renderer->OnUpdate();
            Window->OnUpdate();
        }
        glfwTerminate();
    }
}

