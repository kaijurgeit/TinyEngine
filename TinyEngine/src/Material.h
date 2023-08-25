#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace TE
{
    struct MaterialData
    {
        glm::vec4 BaseColor;
    };
    
    class Shader;

    class Material
    {
    public:
    private:
        std::unique_ptr<Shader> Shader;
    };    
}

