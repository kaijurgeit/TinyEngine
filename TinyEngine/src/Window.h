#pragma once
#include <memory>
#include <string>


namespace TE
{
    struct WindowData
    {
        std::string Title;
        int Width;
        int Height;
    };

    class Window
    {
    public:
        Window(const WindowData& windowData);
        Window(const char* title, int width, int height);
    
    };
}
