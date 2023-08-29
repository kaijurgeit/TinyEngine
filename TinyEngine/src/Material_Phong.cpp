#include "Material_Phong.h"
#include "Shader.h"

namespace TE
{
    Material_Phong::Material_Phong(Shader& shader)
        : Material(shader)
    {
    }

    void Material_Phong::Update(glm::mat4 mvp)
    {
        Material::Update(mvp);
        // data.texture.Bind(0);
        // shader.SetUniform("texture0", 0);
    }
}