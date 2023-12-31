#pragma once
#include <glm/fwd.hpp>
#include "Core.h"
#include "Event.h"

namespace TE
{
    class OtherEvent;
    class InputEvent;
    class Window;
    class Renderer;
    class Camera;
    class Event;
    
    // Abstract Class
    class TE_API Application
    {
    public:        
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event& event);
        
        static Application& Get() { return *instance; }
        static Window& GetWindow() { return *Get().window.get(); }
        static Renderer& GetRenderer() { return *Get().renderer.get(); }
        static Camera& GetCamera() { return *Get().camera.get(); }
        static std::string& GetPath() { return Get().path; }
        static glm::mat4 GetProjection();        
        static float GetDeltaTime() { return Get().deltaTime; }
        
        
    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Camera> camera;
        std::string path;
        float lastFrameTime;
        float deltaTime;
        
        static Application* instance;
        
        void ProcessInput();
        void UpdateDeltaTime();
        void OnInput(InputEvent e); 
        void OnOther(OtherEvent e);   
    };
    
    Application* CreateApplication();
}
