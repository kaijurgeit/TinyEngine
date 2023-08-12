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
    {   // while (!Window->ShouldClose())
        // {
        //     Window->OnUpdate();
        //     Renderer->OnUpdate();
        // }



        // render loop
        // -----------
        while (true)
        {
            // input
            // -----

            // render
            // ------
            Renderer->OnUpdate();

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            Window->OnUpdate();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }
}

