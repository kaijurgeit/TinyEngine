#include "Material.h"

#include "Shader.h"

namespace TE
{
    Material::Material(Shader* shader, glm::vec4 baseColor)
        : shader(shader)
    {
        data.BaseColor = baseColor;
        Create();
    }

    Material::Material(Shader* shader, MaterialData data)
        : shader(shader), data(data)
    {
        
    }
    
    void Material::Create()
    {
        shader->Create();
        shader->Bind();
        shader->SetUniform("color", data.BaseColor);
    }
    
    void Material::Bind()
    {
        shader->Bind();
        shader->SetUniform("color", data.BaseColor);
    }
}
