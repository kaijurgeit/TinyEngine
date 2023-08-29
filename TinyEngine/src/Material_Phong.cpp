#include "Material_Phong.h"
#include "Shader.h"

namespace TE
{

    Material_Phong::Material_Phong(Shader& shader, MaterialData materialData)
        : Material(shader), material(materialData)
    {
        shader.Bind();
        shader.SetUniform("dirLight.direction", dirLight.direction);
        shader.SetUniform("dirLight.ambient", dirLight.ambient);
        shader.SetUniform("dirLight.diffuse", dirLight.diffuse);
        shader.SetUniform("dirLight.specular", dirLight.specular);
    }

    void Material_Phong::Update(glm::mat4 mvp)
    {
        // Material::Update(mvp);
        material.diffuse->Bind(1);
        material.specular->Bind(2);
        shader.SetUniform("texture0", 0);
    }

    void Material_Phong::Update()
    {
        shader.Bind();
        material.diffuse->Bind(1);
        material.specular->Bind(2);
    }
}