#pragma once
#include <string>

namespace TE
{
    class Shader
    {
    public:
        unsigned int Type;
        unsigned int Id;
        std::string Source;
    
        Shader(unsigned int type, const char* path);
        unsigned int Compile();
    
    private:
        void Shader::LogDeleteIfCompilationFails();
    };
    
}
