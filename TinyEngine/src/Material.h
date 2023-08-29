#pragma once
#include <glm/glm.hpp>

namespace TE
{
    class Shader;

    class Material
    {
    public:
        Material(Shader& shader);
        virtual void Update(glm::mat4 mvp);
        
    protected:
        Shader& shader;
    };    
}

