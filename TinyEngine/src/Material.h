#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace TE
{
    struct MaterialData
    {
        glm::vec4 BaseColor;
    };
    
    class Shader;

    class Material
    {
    public:
        Material(Shader* shader, glm::vec4 baseColor);
        Material(Shader* shader, MaterialData data);

        void Update(glm::mat4 mvp);

        Shader* GetShader() const { return shader; }
        MaterialData GetData() const { return data; }
        void SetData(const MaterialData& data) { this->data = data; }
        
    private:
        Shader* shader;
        MaterialData data;
    };    
}

