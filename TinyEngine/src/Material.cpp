#include "Material.h"

#include "Shader.h"

namespace TE
{
    Material::Material(Shader* shader, glm::vec4 baseColor)
        : shader(shader)
    {
        shader->Bind();
        data.BaseColor = baseColor;
    }

    Material::Material(Shader* shader, MaterialData data)
        : shader(shader), data(data)
    {
        
    }

    void Material::Update(glm::mat4 mvp)
    {
        shader->Bind();
        shader->SetUniform("MVP", mvp);
        shader->SetUniform("color", data.BaseColor);
    }
}
