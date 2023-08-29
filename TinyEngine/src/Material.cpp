#include "Material.h"

#include "Application.h"
#include "Camera.h"
#include "Shader.h"

namespace TE
{    
    Material::Material(Shader& shader)
        : shader(shader)
    {
        shader.Bind();
    }

    void Material::Update(glm::mat4 model)
    {
        shader.Bind();
        glm::mat4 mvp = Application::GetProjection() * Application::GetCamera().GetViewMatrix() * model; 
        shader.SetUniform("mvp", mvp);
    }
}
