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
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);
    
    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // camera
    float lastX = 400.f;
    float lastY = 300.f;
    bool firstMouse = true;
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
        
        glfwSetCursorPosCallback(window->GlfwWindow, mouse_callback);
        glfwSetInputMode(window->GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    Application::~Application()
    {
    }
    
    void Application::Run()
    {
        glm::mat4 projection = Projection();

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
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
#pragma endregion PointLights
        
#pragma region phongCube
        Shader phong( {
            ShaderElement(GL_VERTEX_SHADER, path + "shaders/Phong.vert"),
            ShaderElement(GL_FRAGMENT_SHADER, path + "shaders/Phong.frag")});
            
        Texture texDiff(path + "resources/textures/container2.png"); 
        Texture texSpec(path + "resources/textures/container2_specular.png");
        MaterialData materialData = { &texDiff, &texSpec, 32.f };        
        Material_Phong matPhong(phong, materialData);
        
        constexpr glm::vec3 phongCubePos(0.0f, 0.0f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, phongCubePos);
        model = glm::scale(model, glm::vec3(0.5f)); // a smaller cube

        phong.Create();
        phong.Bind();
        phong.SetUniform("projection", projection);
        phong.SetUniform("model", model);

        phong.SetUniform("material.diffuse", 1);
        phong.SetUniform("material.specular", 2);
                // be sure to activate shader when setting uniforms/drawing objects
        
        phong.SetUniform("material.shininess", 32.0f);

        // phong.SetUniform("dirLight.direction", -0.2f, -1.0f, -0.3f);
        // phong.SetUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        // phong.SetUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        // phong.SetUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        phong.SetUniform("pointLights[0].position", pointLightPositions[0]);
        phong.SetUniform("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        phong.SetUniform("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        phong.SetUniform("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        phong.SetUniform("pointLights[0].constant", 1.0f);
        phong.SetUniform("pointLights[0].linear", 0.09f);
        phong.SetUniform("pointLights[0].quadratic", 0.032f);
        // point light 2
        phong.SetUniform("pointLights[1].position", pointLightPositions[1]);
        phong.SetUniform("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        phong.SetUniform("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        phong.SetUniform("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        phong.SetUniform("pointLights[1].constant", 1.0f);
        phong.SetUniform("pointLights[1].linear", 0.09f);
        phong.SetUniform("pointLights[1].quadratic", 0.032f);
        // point light 3
        phong.SetUniform("pointLights[2].position", pointLightPositions[2]);
        phong.SetUniform("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        phong.SetUniform("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        phong.SetUniform("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        phong.SetUniform("pointLights[2].constant", 1.0f);
        phong.SetUniform("pointLights[2].linear", 0.09f);
        phong.SetUniform("pointLights[2].quadratic", 0.032f);
        // point light 4
        phong.SetUniform("pointLights[3].position", pointLightPositions[3]);
        phong.SetUniform("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        phong.SetUniform("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        phong.SetUniform("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        phong.SetUniform("pointLights[3].constant", 1.0f);
        phong.SetUniform("pointLights[3].linear", 0.09f);
        phong.SetUniform("pointLights[3].quadratic", 0.032f);
        
        // spotLight
        phong.SetUniform("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        phong.SetUniform("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        phong.SetUniform("spotLight.specular", 1.0f, 1.0f, 1.0f);
        phong.SetUniform("spotLight.constant", 1.0f);
        phong.SetUniform("spotLight.linear", 0.09f);
        phong.SetUniform("spotLight.quadratic", 0.032f);
        phong.SetUniform("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        phong.SetUniform("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        
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
            const float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            // input
            // -----
            processInput(window->GlfwWindow);
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

            matPhong.Update();

            
            // for (unsigned int i = 0; i < 4; i++)
            // {
            //     model = glm::mat4(1.0f);
            //     model = glm::translate(model, pointLightPositions[i]);
            //     model = glm::scale(model, glm::vec3(0.2f));                
            //     flat.SetUniform("model", model);
            //     renderer->Draw(va, light);
            // }

            phong.Bind();
            phong.SetUniform("view", view);            
            phong.SetUniform("viewPos", camera->GetPosition());
            phong.SetUniform("spotLight.position", camera->GetPosition());
            phong.SetUniform("spotLight.direction", camera->GetFront());
            renderer->Draw(va, phong);

            ourModel.Draw(ourShader);
            
            // glDisable(GL_FALSE);     // uncomment to check debug
            window->OnUpdate();               
        }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    }

    void Application::OnEvent(Event& event)
    {
        std::cout << "Test Event Callback via Bind - " << event.ToString() << std::endl;  
    }

    glm::mat4 Application::Projection()
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
            Application::GetCamera().ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Application::GetCamera().ProcessKeyboard(RIGHT, deltaTime);
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

        Application::GetCamera().ProcessMouseMovement(xoffset, yoffset);
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    // ----------------------------------------------------------------------
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        Application::GetCamera().ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

