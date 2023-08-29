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

    struct DirectionalLight
    {
        glm::vec3 direction = glm::vec3(-0.2, -1.0, -0.3);
        glm::vec3 ambient =  glm::vec3(0.05f, 0.05f, 0.05f);
        glm::vec3 diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
        glm::vec3 specular =   glm::vec3(0.5f, 0.5f, 0.5f);
    };
    
    class Material_Phong : public Material
    {
        
    public:
        Material_Phong(Shader& shader, MaterialData materialData);
        void Update(glm::mat4 mvp) override;
        void Update();
        MaterialData material;
        DirectionalLight dirLight;
    };
}
