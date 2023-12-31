#pragma once
#include <dinput.h>

extern TE::Application* TE::CreateApplication();


int main(int argc, char const *argv[])
{
    std::cout << "TinyEngine..." << std::endl;
    auto app = TE::CreateApplication();
    app->Run();

    delete app;
}
