#pragma once

extern TE::Application* TE::CreateApplication();

int main(int argc, char const *argv[])
{
    printf("Tiny Engine");
    auto app = TE::CreateApplication();
    app->Run();

    delete app;
}
