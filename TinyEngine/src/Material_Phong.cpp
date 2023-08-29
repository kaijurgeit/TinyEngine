#include "Material_Phong.h"

#include "Application.h"
#include "Shader.h"

namespace TE
{


    Material_Phong::Material_Phong(Shader& shader, MaterialData materialData)
        : Material(shader), material(materialData)
    {
        Init();
    }

    void Material_Phong::Init()
    {
        shader.Bind();
        
        SetMaterialUniform();        
        SetDirectionalLightUniform();
        SetSpotlightUniform();
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


    void Material_Phong::Update(glm::mat4 model)
    {   
        shader.Bind();        
        shader.SetUniform("projection", Application::GetProjection());
        shader.SetUniform("model", model);
        material.diffuse->Bind(1);
        material.specular->Bind(2);
    }
}