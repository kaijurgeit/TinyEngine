#include "Application.h"

#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Renderer.h"
#include "Window.h"
#include "ShaderElement.h"
#include "Shader.h"
#include "FileSystem.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

namespace TE
{
#pragma region globals
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);
    
    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    float lastX = 400.f;
    float lastY = 300.f;
    bool firstMouse = true;
#pragma endregion globals


    Application::Application()    
    {
        Window = std::make_unique<TE::Window>("TinyEngine App", 800, 600);
        Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        Renderer = std::make_unique<TE::Renderer>();
        
        glfwSetCursorPosCallback(Window->GlfwWindow, mouse_callback);
        glfwSetInputMode(Window->GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    Application::~Application()
    {
    }
    
    void Application::Run()
    {
        // get path
        std::filesystem::path p(__FILE__);
        const std::string Path = p.parent_path().parent_path().string() + "/";
#pragma region camera
        // viewer matrix transformations
        glm::mat4 projection = glm::perspective(
            glm::radians(45.f),
            static_cast<float>(Window->GetWidth()) / static_cast<float>(Window->GetHeight()),
        0.1f, 100.0f);
#pragma endregion camera
        
#pragma region light
        constexpr glm::vec3 lightPos(1.0f, 0.5f, 1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        
        // load cube vertex data
        const std::vector<float> vertices = TE::FileSystem::FileToFloatVector((Path + "resources/raw/cube_tex_normals.txt").c_str());
        
        // build and compile Shaders
        Shader light( {
            ShaderElement(GL_VERTEX_SHADER, (Path + "shaders/Light.vert").c_str()),
            ShaderElement(GL_FRAGMENT_SHADER, (Path + "shaders/Light.frag").c_str())});
        light.Create();
        light.Bind();
        light.SetUniform("projection", projection);
        light.SetUniform("model", model);
#pragma endregion light

#pragma region texCube
        constexpr glm::vec3 texCubePos(0.5f, 1.0f, 0.5f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, texCubePos);
        model = glm::scale(model, glm::vec3(0.5f)); // a smaller cube

        Shader texCube( {
            ShaderElement(GL_VERTEX_SHADER, (Path + "shaders/Texture.vert").c_str()),
            ShaderElement(GL_FRAGMENT_SHADER, (Path + "shaders/Texture.frag").c_str())});
        texCube.Create();
        texCube.Bind();
        texCube.SetUniform("projection", projection);
        texCube.SetUniform("model", model);
        texCube.SetUniform("texture0", 0);

        Texture albedo((Path + "resources/textures/container.jpg").c_str()); 
#pragma endregion texCube

#pragma region phongCube
        constexpr glm::vec3 phongCubePos(0.0f, 0.0f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, phongCubePos);
        model = glm::scale(model, glm::vec3(0.5f)); // a smaller cube

        Shader phongCube( {
            ShaderElement(GL_VERTEX_SHADER, (Path + "shaders/Phong.vert").c_str()),
            ShaderElement(GL_FRAGMENT_SHADER, (Path + "shaders/Phong.frag").c_str())});
        phongCube.Create();
        phongCube.Bind();
        phongCube.SetUniform("projection", projection);
        phongCube.SetUniform("model", model);
        
        // Texture diffuseMap((Path + "resources/textures/container2.png").c_str()); 
#pragma endregion phongCube
        
        VertexArray va;
        VertexBuffer vb(vertices.data(), vertices.size() * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Add<float>(3);
        layout.Add<float>(3);
        layout.Add<float>(2);
        va.Bind();
        va.AddBuffer(vb, layout);

        
        while (true)
        {
            // per-frame time logic
            // --------------------
            const float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            // input
            // -----
            processInput(Window->GlfwWindow);
            Renderer->Clear();
            glm::mat4 view = camera.GetViewMatrix();

            light.Bind();
            light.SetUniform("view", view);
            Renderer->Draw(va, light);
            
            texCube.Bind();
            texCube.SetUniform("view", view);
            Renderer->Draw(va, texCube);

            phongCube.Bind();
            phongCube.SetUniform("view", view);
            Renderer->Draw(va, phongCube);
            
            // glDisable(GL_FALSE);     // uncomment to check debug
            Window->OnUpdate();               
        }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    }

    void Application::OnEvent(Event& event)
    {
        std::cout << "Test Event Callback via Bind - " << event.ToString() << std::endl;  
    }

    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------
    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    // ----------------------------------------------------------------------
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

