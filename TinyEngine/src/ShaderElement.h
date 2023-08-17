#pragma once
#include <string>

#include "Core.h"

namespace TE
{
    class ShaderElement
    {
    public:
        unsigned int Type;
        unsigned int Id;
        std::string Source;
    
        ShaderElement(unsigned int type, const char* path);
        unsigned int Compile();
    
    private:
        void ShaderElement::LogDeleteIfCompilationFails();
    };
    
}
