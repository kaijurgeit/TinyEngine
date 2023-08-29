#include "Material_Flat.h"

#include "Shader.h"

namespace TE
{    
    Material_Flat::Material_Flat(Shader* shader, glm::vec4 baseColor)
        : shader(shader)
    {
        shader->Bind();
        data.color = baseColor;
    }

    Material_Flat::Material_Flat(Shader* shader, MaterialData data)
        : shader(shader), data(data)
    {
        
    }

    void Material_Flat::Update(glm::mat4 mvp)
    {
        shader->Bind();
        shader->SetUniform("mvp", mvp);
        shader->SetUniform("color", data.color);
    }
}
