#pragma once
#include <glad/glad.h>"
#include <GLFW/glfw3.h>

namespace TE
{
    class IndexBuffer;
    class VertexArray;
}

namespace TE
{
    class Renderer
    {
    public:
        Renderer();
        void OnUpdate();

        // void Draw(const VertexArray& va, const IndexBuffer& indexBuffer, const ShaderElement& shader) const;
    };
}
