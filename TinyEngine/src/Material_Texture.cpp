#include "Material_Texture.h"

#include "Shader.h"

namespace TE
{
    Material_Texture::Material_Texture(Shader& shader, std::string texPath)
        : Material(shader), data({Texture(texPath)})
    {
    }

    void Material_Texture::Update(glm::mat4 mvp)
    {
        Material::Update(mvp);
        data.texture.Bind(0);
        shader.SetUniform("texture0", 0);
    }
}