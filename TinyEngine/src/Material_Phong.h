#pragma once
#include "Material.h"
#include "Texture.h"

namespace TE
{    
    class Material_Phong : public Material
    {
        struct MaterialData
        {
            Texture texture;
        };
        
    public:
        Material_Phong(Shader& shader);
        void Update(glm::mat4 mvp) override;
        // MaterialData data;
    };
}
