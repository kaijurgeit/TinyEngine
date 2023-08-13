#include "Application.h"

#include <fstream>
#include <filesystem>

#include <glad/glad.h>

#include "Renderer.h"
#include "Window.h"

#include "Shader.h"
#include "Program.h"

namespace TE
{
    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

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
        std::filesystem::path p(__FILE__);
        const std::string Path = p.parent_path().parent_path().string() + "/";

        // build and compile shaders
        // -------------------------
        Program ourShader( {
            Shader(GL_VERTEX_SHADER, (Path + "shaders/Model.vert").c_str()),
            Shader(GL_FRAGMENT_SHADER, (Path + "shaders/Model.frag").c_str())
        });
        ourShader.Create();
        
        while (true)
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            Renderer->OnUpdate();
            Window->OnUpdate();
        }
    }
}

