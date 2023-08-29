#include "Material_Flat.h"

#include "Application.h"
#include "Shader.h"
#include "glad/glad.h"

namespace TE
{
    Material_Flat::Material_Flat(Shader& shader, glm::vec4 baseColor)
        : Material(shader)
    {
        data.color = baseColor;
    }

    void Material_Flat::Update(glm::mat4 mvp)
    {
        Material::Update(mvp);
        shader.SetUniform("color", data.color);
    }
}
