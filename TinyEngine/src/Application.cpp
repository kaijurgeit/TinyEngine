#include "Application.h"

#include <filesystem>
// #include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Renderer.h"
#include "Window.h"
#include "ShaderElement.h"
#include "Shader.h"
#include "FileSystem.h"
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
        Renderer = std::make_unique<TE::Renderer>();
        
        glfwSetCursorPosCallback(Window->GlfwWindow, mouse_callback);
        glfwSetInputMode(Window->GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
#pragma endregion camera
        
#pragma region light
        // get path
        std::filesystem::path p(__FILE__);
        const std::string Path = p.parent_path().parent_path().string() + "/";
        
        // load cube vertex data
        std::vector<float> vertices = TE::FileSystem::FileToFloatVector((Path + "resources/raw/cube.txt").c_str());
        
        // build and compile Shaders
        Shader light( {
            ShaderElement(GL_VERTEX_SHADER, (Path + "Shaders/Light.vert").c_str()),
            ShaderElement(GL_FRAGMENT_SHADER, (Path + "Shaders/Light.frag").c_str())
        });
        light.Create();

        const glm::vec3 lightPos(0.5f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube

        light.Bind();
        light.SetUniform("projection", projection);
        light.SetUniform("view", view);
        light.SetUniform("model", model);
#pragma endregion light

        VertexArray va;
        VertexBuffer vb(vertices.data(), vertices.size() * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Add<float>(3);
        va.Bind();
        va.AddBuffer(vb, layout);
        
        while (true)
        {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        // -----
        processInput(Window->GlfwWindow);

        Renderer->Clear();


#pragma region lightCube            
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube

        light.Bind();
        light.SetUniform("projection", projection);
        light.SetUniform("view", view);
        light.SetUniform("model", model);        
        
        Renderer->Draw(va, light);

        float scale = 1.1f;
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        
        
#pragma endregion lightCube
            
        Window->OnUpdate();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
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

