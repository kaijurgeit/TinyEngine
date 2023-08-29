#pragma once

#include "Material.h"

namespace TE
{
    class Material_Flat : public Material
    {
    public:
        Material_Flat(Shader& shader, glm::vec4 baseColor);
        void Update(glm::mat4 mvp) override;
    };    
}

