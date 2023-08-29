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
        
        shader.SetUniform("material.diffuse", 1);
        shader.SetUniform("material.specular", 2);
        shader.SetUniform("material.shininess", material.shininess);
        
        shader.SetUniform("dirLight.direction", dirLight.direction);
        shader.SetUniform("dirLight.ambient", dirLight.ambient);
        shader.SetUniform("dirLight.diffuse", dirLight.diffuse);
        shader.SetUniform("dirLight.specular", dirLight.specular);
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