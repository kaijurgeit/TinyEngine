#pragma once
#include <string>

namespace TE
{
    class Shader
    {
    public:
        unsigned int type;
        unsigned int id;
        std::string source;
    
        Shader(unsigned int type, const char* path);
        unsigned int Compile();
    
    private:
        void Shader::LogDeleteIfCompilationFails();
    };
    
}
