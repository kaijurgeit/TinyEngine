#pragma once
#include <glm/glm.hpp>

namespace TE
{
    struct MaterialData
    {
        glm::vec4 color;
    };

    struct MaterialData;
    class Shader;

    class Material
    {
    public:
        Material(Shader& shader);
        virtual void Update(glm::mat4 mvp);
        
    protected:
        Shader& shader;
        MaterialData data;
    };    
}

