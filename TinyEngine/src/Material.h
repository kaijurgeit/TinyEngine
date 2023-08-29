#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace TE
{
    struct MaterialData
    {
        glm::vec4 color;
    };
    
    class Shader;

    class Material
    {
    public:
        Material(Shader* shader, glm::vec4 baseColor);
        Material(Shader* shader, MaterialData data);
        void Update(glm::mat4 mvp);

        
    private:
        Shader* shader;
        MaterialData data;
    };    
}

