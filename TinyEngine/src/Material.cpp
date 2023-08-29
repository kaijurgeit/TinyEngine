#include "Material.h"

#include "Shader.h"

namespace TE
{    
    Material::Material(Shader& shader)
        : shader(shader)
    {
        shader.Bind();
    }

    void Material::Update(glm::mat4 mvp)
    {
        shader.Bind();
        shader.SetUniform("mvp", mvp);
    }
}
