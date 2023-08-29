#pragma once
#include <string>

#include "Material.h"
#include "Texture.h"

namespace TE
{
    class Material_Texture : public Material
    {
        struct MaterialData
        {
            Texture texture;
        };
        
    public:
        Material_Texture(Shader& shader, std::string texPath);
        void Update(glm::mat4 mvp) override;
        
    private:
        MaterialData data;
    };    
}
