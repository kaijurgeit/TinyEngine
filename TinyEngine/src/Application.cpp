#include "Application.h"
#include "Window.h"

namespace TE
{
    Application::Application()
    {
        Window = std::make_unique<TE::Window>("TinyEngine App", 800, 600);
    }
    
    Application::~Application()
    {
    }
    
    void Application::Run()
    {
        while (true);        
    }
}

