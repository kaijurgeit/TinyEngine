#pragma once
#include <string>

#include "Core.h"
#include "Shader.h"

namespace TE
{   
    class TE_API ShaderElement
    {
        friend class Shader;
    public:
        ShaderElement(unsigned int type, const char* path);
        ShaderElement(unsigned int type, std::string path);
        unsigned int Compile();
    
    private:
        void ShaderElement::LogDeleteIfCompilationFails();
        
        unsigned int Type;
        std::string Source;
        unsigned int Id = -1;
    };
    
}
