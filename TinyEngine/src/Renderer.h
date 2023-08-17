#pragma once

#include "Core.h"

namespace TE
{
    class Shader;
    class IndexBuffer;
    class VertexArray;
    
    class TE_API Renderer
    {
    public:
        Renderer();
        void Clear();

        void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
        void Draw(const VertexArray& vertexArray, const Shader& shader) const;
    };
}
