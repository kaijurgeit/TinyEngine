#pragma once
#include <array>

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
    
    struct PointLight {
        glm::vec3 position;

        float constant;
        float linear;
        float quadratic;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct SpotLight {
        glm::vec3 position;
        glm::vec3 direction;
        
        float cutOff = glm::cos(glm::radians(5.0));
        float outerCutOff = glm::cos(glm::radians(10.0));
        float constant = 1.0;
        float linear = 0.09;
        float quadratic = 0.032f;

        glm::vec3 ambient = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
        glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
    };
    
    
    class Material_Phong : public Material
    {
        
    public:
        Material_Phong(Shader& shader, MaterialData materialData, std::array<glm::vec3, 4> pointLightPositions);
        void SetPointLights(std::array<glm::vec3, 4> pointLightPositions);
        void SetPointLightUniforms();
        void Init();
        void SetDirectionalLightUniform();
        void SetMaterialUniform();
        void SetSpotlightUniform();
        void Update(glm::mat4 model) override;
        MaterialData material;
        DirectionalLight dirLight;
        PointLight pointLight;
        SpotLight spotLight;
        std::array<PointLight, 4> pointLights;
    };
}
