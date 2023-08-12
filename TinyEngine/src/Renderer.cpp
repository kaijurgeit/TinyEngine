#include "Renderer.h"

#include <iostream>

#include "Core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace TE
{
    Renderer::Renderer()
    { 
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;        
        } 
    }

    void Renderer::OnUpdate()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }    
}
