#pragma once
#include "Material.h"
#include "Texture.h"

namespace TE
{    
    struct MaterialData
    {
        Texture* diffuse;
        Texture* specular;
        float shininess;
    };
    class Material_Phong : public Material
    {
        
    public:
        Material_Phong(Shader& shader, MaterialData materialData);
        void Update(glm::mat4 mvp) override;
        void Update();
        MaterialData material;
    };
}
