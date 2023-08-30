#include "Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>
#include <glm/fwd.hpp>

#include "Camera.h"
#include "Renderer.h"
#include "Window.h"
#include "ShaderElement.h"
#include "Shader.h"
#include "FileSystem.h"
#include "Model.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Material_Flat.h"
#include "Material_Phong.h"
#include "Material_Texture.h"
#include "Mesh.h"

namespace TE
{
    Application* Application::instance = nullptr;
#pragma region globals
    void processInput(GLFWwindow *window);
#pragma endregion globals

    Application::Application()    
    {
        instance = this;
        window = std::make_unique<Window>("TinyEngine App", 800, 600);
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        renderer = std::make_unique<Renderer>();
        camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
        
        std::filesystem::path p(__FILE__);
        path = p.parent_path().parent_path().string() + "/";
    }
    
    Application::~Application()
    {
    }
    
    void Application::Run()
    {
        glm::mat4 projection = GetProjection();

#pragma region vertexData
        const std::vector<float> vertices = FileSystem::FileToFloatVector(path + "resources/raw/cube_tex_normals.txt");
        VertexArray va;
        VertexBuffer vb(vertices.data(), vertices.size() * sizeof(float));
    
        VertexBufferLayout layout;
        layout.Add<float>({3, 3, 2});
        va.Bind();
        va.AddBuffer(vb, layout);
#pragma endregion vertexData
        
        glm::mat4 model = glm::mat4(1.0f);

        Shader shaFlat( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Flat.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Flat.frag")});
        
#pragma region flatCubes
        Material_Flat flatRed(shaFlat, glm::vec4(1.0, 0.0, 0.0, 1.0));
        Mesh redCube = Mesh::CreateCube(&va, &flatRed, glm::vec3(1.0f, 0.5f, 0.5f), 0.2);
        
        Material_Flat flatGreen(shaFlat, glm::vec4(0.0, 1.0, 0.0, 1.0));
        Mesh greenCube = Mesh::CreateCube(&va, &flatGreen, glm::vec3(1.0f, 0.5f, 1.0f), 0.2);
        
        Material_Flat flatBlue(shaFlat, glm::vec4(0.0, 0.0, 1.0, 1.0));
        Mesh blueCube = Mesh::CreateCube(&va, &flatBlue, glm::vec3(1.0f, 0.5f, 1.5f), 0.2);
        
        Material_Flat flatYellow(shaFlat, glm::vec4(1.0, 1.0, 0.0, 1.0));
        Mesh yellowCube = Mesh::CreateCube(&va, &flatYellow, glm::vec3(1.0f, 0.5f, 2.0f), 0.2);
        
        Material_Flat flatCyan(shaFlat, glm::vec4(0.0, 1.0, 1.0, 1.0));
        Mesh cyanCube = Mesh::CreateCube(&va, &flatCyan, glm::vec3(1.0f, 0.5f, 2.5f), 0.2);
        
        Material_Flat flatMagenta(shaFlat, glm::vec4(1.0, 0.0, 1.0, 1.0));
        Mesh magentaCube = Mesh::CreateCube(&va, &flatMagenta, glm::vec3(1.0f, 0.5f, 3.0f), 0.2);
        
        Material_Flat flatWhite(shaFlat, glm::vec4(1.0, 1.0, 1.0, 1.0));
        Mesh whiteCube = Mesh::CreateCube(&va, &flatWhite, glm::vec3(1.0f, 0.5f, 3.5f), 0.2);        
#pragma endregion flatCubes

#pragma region texCube
        Shader shaTexture( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Texture.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Texture.frag")});

        Texture texContainer(path + "resources/textures/container.jpg");
        Material_Texture matContainer(shaTexture, &texContainer);
        Mesh containerCube = Mesh::CreateCube(&va, &matContainer, glm::vec3(.0f, 0.5f, 4.0f), 0.5);
#pragma endregion texCube

#pragma region PointLights
            // positions of the point lights
        glm::vec3 pointLightPositions_[] = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
        };
        std::array<glm::vec3, 4> &pointLightPositions = reinterpret_cast<std::array<glm::vec3, 4>&>(pointLightPositions_);
        
        glm::vec3 phongCubePosition(0.0, 0.0, 0.0);
        for (glm::vec3 pointLightPosition : pointLightPositions)
        {
            phongCubePosition += pointLightPosition;
        }
        phongCubePosition *= 1.0 / pointLightPositions.size();
#pragma endregion PointLights
        
#pragma region phongCube
        Shader phong( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Phong.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Phong.frag")});
            
        Texture texDiff(path + "resources/textures/container2.png"); 
        Texture texSpec(path + "resources/textures/container2_specular.png");
        MaterialData materialData = { &texDiff, &texSpec, 32.f };        
        Material_Phong matPhong(phong, materialData, pointLightPositions);
        Mesh phongCube = Mesh::CreateCube(&va, &matPhong, phongCubePosition, 0.5);
#pragma endregion phongCube

#pragma region Model
        
        Shader ourShader( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Model.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Model.frag")});
        ourShader.Create();
        
        Model ourModel((path + "resources/objects/cyborg/cyborg.obj").c_str());
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.Bind();
        ourShader.SetUniform("model", model);
#pragma endregion Model
        while (true)
        {
            // per-frame time logic
            // --------------------
            const float currentFrameTime = static_cast<float>(glfwGetTime());
            deltaTime = currentFrameTime - lastFrameTime;
            lastFrameTime = currentFrameTime;
            
            // processInput(window->GlfwWindow);
            renderer->Clear();
            glm::mat4 view = camera->GetViewMatrix();

            redCube.Draw();
            greenCube.Draw();
            blueCube.Draw();
            yellowCube.Draw();
            cyanCube.Draw();
            magentaCube.Draw();
            whiteCube.Draw();

            containerCube.Draw();

            matPhong.Update(model);

            phongCube.Draw();

            ourModel.Draw(ourShader);

            for (const glm::vec3& pointLightPosition : pointLightPositions)
            {
                Material_Flat flatWhite(shaFlat, glm::vec4(1.0, 1.0, 1.0, 1.0));
                Mesh whiteCube = Mesh::CreateCube(&va, &flatWhite, pointLightPosition, 0.1);
                whiteCube.Draw();
            }

            
            window->OnUpdate();               
        }
    }

    void Application::OnEvent(Event& event)
    {
        std::cout << "Test Event Callback via Bind - " << event.ToString() << std::endl;  
    }

    glm::mat4 Application::GetProjection()
    {
        return glm::perspective(
            glm::radians(GetCamera().GetZoom()),
            static_cast<float>(GetWindow().GetWidth()) / static_cast<float>(GetWindow().GetHeight()),
        0.1f, 100.0f);
    }

    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(FORWARD, Application::GetDeltaTime());
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(BACKWARD, Application::GetDeltaTime());
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(LEFT, Application::GetDeltaTime());
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(RIGHT, Application::GetDeltaTime());
    }
}

