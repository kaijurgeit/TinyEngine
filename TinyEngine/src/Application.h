#pragma once

#include "Core.h"

namespace TE
{
    // Abstract Class
    class TE_API Application
    {
    private:
    public:
        Application();
        virtual ~Application();
        void Run();
    };
    
    Application* CreateApplication();
}