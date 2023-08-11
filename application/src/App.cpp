#include <iostream>
#include <TinyEngine.h>

class App : public TE::Application
{
public:
    App()
    {
        
    }

    ~App()
    {

    }
};

TE::Application* TE::CreateApplication()
{
    return new App();
}
