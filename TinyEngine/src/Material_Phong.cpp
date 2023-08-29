#include "Material_Phong.h"

#include "Application.h"
#include "Shader.h"

namespace TE
{


    Material_Phong::Material_Phong(Shader& shader, MaterialData materialData, std::array<glm::vec3, 4> pointLightPositions)
        : Material(shader), material(materialData)
    {
        SetPointLights(pointLightPositions);
        Init();
    }
    
    void Material_Phong::SetPointLights(std::array<glm::vec3, 4> pointLightPositions)
    {
        pointLights[0].position = pointLightPositions[0];
        pointLights[0].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLights[0].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLights[0].constant = 1.0f;
        pointLights[0].linear = 0.09f;
        pointLights[0].quadratic = 0.032f;
        
        pointLights[1].position = pointLightPositions[1];
        pointLights[1].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLights[1].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLights[1].specular = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLights[1].constant = 1.0f;
        pointLights[1].linear = 0.09f;
        pointLights[1].quadratic = 0.032f;
        
        pointLights[2].position = pointLightPositions[2];
        pointLights[2].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLights[2].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLights[2].specular = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLights[2].constant = 1.0f;
        pointLights[2].linear = 0.09f;
        pointLights[2].quadratic = 0.032f;
        
        pointLights[3].position = pointLightPositions[3];
        pointLights[3].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLights[3].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLights[3].specular = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLights[3].constant = 1.0f;
        pointLights[3].linear = 0.09f;
        pointLights[3].quadratic = 0.032f;
    }

    void Material_Phong::Init()
    {
        shader.Bind();
        
        SetMaterialUniform();        
        SetDirectionalLightUniform();
        SetSpotlightUniform();
        SetPointLightUniforms();
    }
    
    void Material_Phong::SetDirectionalLightUniform()
    {
        shader.SetUniform("dirLight.direction", dirLight.direction);
        shader.SetUniform("dirLight.ambient", dirLight.ambient);
        shader.SetUniform("dirLight.diffuse", dirLight.diffuse);
        shader.SetUniform("dirLight.specular", dirLight.specular);
    }

    void Material_Phong::SetMaterialUniform()
    {
        shader.SetUniform("material.diffuse", 1);
        shader.SetUniform("material.specular", 2);
        shader.SetUniform("material.shininess", material.shininess);
    }

    void Material_Phong::SetSpotlightUniform()
    {
        shader.SetUniform("spotLight.ambient", spotLight.ambient);
        shader.SetUniform("spotLight.diffuse", spotLight.diffuse);
        shader.SetUniform("spotLight.specular", spotLight.specular);
        shader.SetUniform("spotLight.constant", spotLight.constant);
        shader.SetUniform("spotLight.linear", spotLight.linear);
        shader.SetUniform("spotLight.quadratic", spotLight.quadratic);
        shader.SetUniform("spotLight.cutOff", spotLight.cutOff);
        shader.SetUniform("spotLight.outerCutOff", spotLight.outerCutOff);
    }

    void Material_Phong::SetPointLightUniforms()
    {
        shader.SetUniform("pointLights[0].position", pointLights[0].position);
        shader.SetUniform("pointLights[0].ambient", pointLights[0].ambient);
        shader.SetUniform("pointLights[0].diffuse", pointLights[0].diffuse);
        shader.SetUniform("pointLights[0].specular", pointLights[0].specular);
        shader.SetUniform("pointLights[0].constant", pointLights[0].constant);
        shader.SetUniform("pointLights[0].linear", pointLights[0].linear);
        
        shader.SetUniform("pointLights[0].quadratic", pointLights[0].quadratic);
        shader.SetUniform("pointLights[1].position", pointLights[1].position);
        shader.SetUniform("pointLights[1].ambient", pointLights[1].ambient);
        shader.SetUniform("pointLights[1].diffuse", pointLights[1].diffuse);
        shader.SetUniform("pointLights[1].specular", pointLights[1].specular);
        shader.SetUniform("pointLights[1].constant", pointLights[1].constant);
        shader.SetUniform("pointLights[1].linear", pointLights[1].linear);
        shader.SetUniform("pointLights[1].quadratic", pointLights[1].quadratic);
        
        shader.SetUniform("pointLights[2].position", pointLights[2].position);
        shader.SetUniform("pointLights[2].ambient", pointLights[2].ambient);
        shader.SetUniform("pointLights[2].diffuse", pointLights[2].diffuse);
        shader.SetUniform("pointLights[2].specular", pointLights[2].specular);
        shader.SetUniform("pointLights[2].constant", pointLights[2].constant);
        shader.SetUniform("pointLights[2].linear", pointLights[2].linear);
        shader.SetUniform("pointLights[2].quadratic", pointLights[2].quadratic);
        
        shader.SetUniform("pointLights[3].position", pointLights[3].position);
        shader.SetUniform("pointLights[3].ambient", pointLights[3].ambient);
        shader.SetUniform("pointLights[3].diffuse", pointLights[3].diffuse);
        shader.SetUniform("pointLights[3].specular", pointLights[3].specular);
        shader.SetUniform("pointLights[3].constant", pointLights[3].constant);
        shader.SetUniform("pointLights[3].linear", pointLights[3].linear);
        shader.SetUniform("pointLights[3].quadratic", pointLights[3].quadratic);
    }


    void Material_Phong::Update(glm::mat4 model)
    {   
        shader.Bind();        
        shader.SetUniform("projection", Application::GetProjection());
        shader.SetUniform("model", model);
        material.diffuse->Bind(1);
        material.specular->Bind(2);
    }
}