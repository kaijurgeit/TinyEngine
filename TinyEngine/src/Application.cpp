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

    Application::Application()    
    {
        instance = this;
        window = std::make_unique<Window>("TinyEngine App", 1200, 800);
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        renderer = std::make_unique<Renderer>();
        camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
        
        std::filesystem::path p(__FILE__);
        path = p.parent_path().parent_path().string() + "/";
    }
    
    Application::~Application()
    {
    }

    void Application::UpdateDeltaTime()
    { 
        const float currentFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
    }

    void Application::Run()
    {

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

        Shader flatShader( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Flat.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Flat.frag")});
        
#pragma region flatCubes
        Material_Flat flatRed(flatShader, glm::vec4(1.0, 0.0, 0.0, 1.0));
        Mesh redCube = Mesh::CreateCube(&va, &flatRed, glm::vec3(1.0f, 0.5f, 0.5f), 0.2);
        
        Material_Flat flatGreen(flatShader, glm::vec4(0.0, 1.0, 0.0, 1.0));
        Mesh greenCube = Mesh::CreateCube(&va, &flatGreen, glm::vec3(1.0f, 0.5f, 1.0f), 0.2);
        
        Material_Flat flatBlue(flatShader, glm::vec4(0.0, 0.0, 1.0, 1.0));
        Mesh blueCube = Mesh::CreateCube(&va, &flatBlue, glm::vec3(1.0f, 0.5f, 1.5f), 0.2);
        
        Material_Flat flatYellow(flatShader, glm::vec4(1.0, 1.0, 0.0, 1.0));
        Mesh yellowCube = Mesh::CreateCube(&va, &flatYellow, glm::vec3(1.0f, 0.5f, 2.0f), 0.2);
        
        Material_Flat flatCyan(flatShader, glm::vec4(0.0, 1.0, 1.0, 1.0));
        Mesh cyanCube = Mesh::CreateCube(&va, &flatCyan, glm::vec3(1.0f, 0.5f, 2.5f), 0.2);
        
        Material_Flat flatMagenta(flatShader, glm::vec4(1.0, 0.0, 1.0, 1.0));
        Mesh magentaCube = Mesh::CreateCube(&va, &flatMagenta, glm::vec3(1.0f, 0.5f, 3.0f), 0.2);
        
        Material_Flat flatWhite(flatShader, glm::vec4(1.0, 1.0, 1.0, 1.0));
        Mesh whiteCube = Mesh::CreateCube(&va, &flatWhite, glm::vec3(1.0f, 0.5f, 3.5f), 0.2);        
#pragma endregion flatCubes

#pragma region texCube
        Shader textureShader( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Texture.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Texture.frag")});

        Texture containerTex(path + "resources/textures/container.jpg");
        Material_Texture containerMat(textureShader, &containerTex);
        Mesh texMesh = Mesh::CreateCube(&va, &containerMat, glm::vec3(.0f, 0.5f, 4.0f), 0.5);
#pragma endregion texCube

#pragma region PointLights
        std::array<glm::vec3, 4> pointLightPositions =
        {
            glm::vec3( 0.7f,  0.2f,  -1.0f),
            glm::vec3( 1.3f, -1.3f, 1.0f),
            glm::vec3(1.0f,  1.0f, 2.0f),
            glm::vec3( 0.0f,  0.0f, 1.5f)
        };
        
        glm::vec3 phongCubePosition(0.0, 0.0, 0.0);
        for (glm::vec3 pointLightPosition : pointLightPositions)
        {
            phongCubePosition += pointLightPosition;
        }
        phongCubePosition *= 1.0 / pointLightPositions.size();
        phongCubePosition = {-0.2f, 0.0f, 0.5f};
#pragma endregion PointLights
        
#pragma region phongCube
        Shader phongShader( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Phong.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Phong.frag")});
            
        Texture diffuseTex(path + "resources/textures/container2.png"); 
        Texture specularTex(path + "resources/textures/container2_specular.png");
        MaterialData materialData = { &diffuseTex, &specularTex, 32.f };        
        Material_Phong phongMat(phongShader, materialData, pointLightPositions);
        Mesh phongMesh = Mesh::CreateCube(&va, &phongMat, phongCubePosition, 0.5);
#pragma endregion phongCube

#pragma region Model
        
        Shader modelShader( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Model.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Model.frag")});
        modelShader.Create();
        
        Model sampleModel((path + "resources/objects/cyborg/cyborg.obj").c_str());
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        modelShader.Bind();
        modelShader.SetUniform("model", model);
#pragma endregion Model
        while (true)
        {
            UpdateDeltaTime();
            
            ProcessInput();
            renderer->Clear();

            // Colorful flat Cubes
            redCube.Draw();
            greenCube.Draw();
            blueCube.Draw();
            yellowCube.Draw();
            cyanCube.Draw();
            magentaCube.Draw();
            whiteCube.Draw();

            // Texture Cube
            texMesh.Draw();

            // Phong Cube
            phongMesh.Draw();

            // Model
            sampleModel.Draw(modelShader);

            // Point lights visualized as little white cubes
            for (const glm::vec3& pointLightPosition : pointLightPositions)
            {
                Material_Flat flatWhite(flatShader, glm::vec4(1.0, 1.0, 1.0, 1.0));
                Mesh whiteCube = Mesh::CreateCube(&va, &flatWhite, pointLightPosition, 0.1);
                whiteCube.Draw();
            }
            
            window->OnUpdate();               
        }
    }

    void Application::OnEvent(Event& event)
    {
        std::cout << "Test Event Callback via Bind - " << event.ToString() << std::endl;
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<InputEvent>(TE_BIND(&Application::OnInput));
        dispatcher.Dispatch<OtherEvent>(std::bind(&Application::OnOther, this, std::placeholders::_1));
    }

    glm::mat4 Application::GetProjection()
    {
        return glm::perspective(
            glm::radians(GetCamera().GetZoom()),
            static_cast<float>(GetWindow().GetWidth()) / static_cast<float>(GetWindow().GetHeight()),
        0.1f, 100.0f);
    }

    void Application::OnInput(InputEvent e)
    {
        // Application::processInput();
    }

    void Application::OnOther(OtherEvent e)
    {   
        std::cout << "Other Event" << std::endl;
    }

    void Application::ProcessInput()
    {
        if (glfwGetKey(window->glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->glfwWindow, true);

        if (glfwGetKey(window->glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(EDirection::Forward, Application::GetDeltaTime());
        if (glfwGetKey(window->glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(EDirection::Backward, Application::GetDeltaTime());
        if (glfwGetKey(window->glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(EDirection::Left, Application::GetDeltaTime());
        if (glfwGetKey(window->glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(EDirection::Right, Application::GetDeltaTime());
    }
}

