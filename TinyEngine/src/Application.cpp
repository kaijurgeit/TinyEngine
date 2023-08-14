#include "Application.h"

#include <filesystem>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "Window.h"
#include "Shader.h"
#include "Program.h"
#include "FileSystem.h"

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
#pragma region camera
        // viewer matrix transformations
        glm::mat4 projection = glm::perspective(
            glm::radians(45.f),
            static_cast<float>(Window->Width) / static_cast<float>(Window->Height),
        0.1f, 100.0f);
        const glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        const glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 view =glm::lookAt(position, position + front, up);
        glm::mat4 model = glm::mat4(1.0f);
#pragma endregion camera
        
#pragma region light
        // get path
        std::filesystem::path p(__FILE__);
        const std::string Path = p.parent_path().parent_path().string() + "/";
        
        // load cube vertex data
        std::vector<float> vertices = TE::FileSystem::FileToFloatVector((Path + "resources/raw/cube.txt").c_str());
        
        // build and compile shaders
        Program lightCube( {
            Shader(GL_VERTEX_SHADER, (Path + "shaders/Light.vert").c_str()),
            Shader(GL_FRAGMENT_SHADER, (Path + "shaders/Light.frag").c_str())
        });
        lightCube.Create();
        
        glm::vec3 lightPos(1.2f, 1.0f, 1.5f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube

        lightCube.Use();
        lightCube.SetUniform("projection", projection);
        lightCube.SetUniform("view", view);
        lightCube.SetUniform("model", model);
#pragma endregion light

#pragma region glBuffers
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        unsigned int lightCubeVAO;
        glGenVertexArrays(1, &lightCubeVAO);
        glBindVertexArray(lightCubeVAO);

        // note that we update the lamp's position attribute's stride to reflect the updated buffer data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
#pragma endregion glBuffers

        
        while (true)
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
            Renderer->OnUpdate();
            Window->OnUpdate();
        }
    }
}

