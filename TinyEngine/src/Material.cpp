﻿#include "Material.h"

#include "Shader.h"

namespace TE
{    
    Material::Material(Shader* shader, glm::vec4 baseColor)
        : shader(shader)
    {
        shader->Bind();
        data.color = baseColor;
    }

    Material::Material(Shader* shader, MaterialData data)
        : shader(shader), data(data)
    {
        
    }

    void Material::Update(glm::mat4 mvp)
    {
        shader->Bind();
        shader->SETUNIFORM(mvp);
        shader->SETUNIFORM(data.color);
        shader->SetUniform("color", data.color);
    }
}
