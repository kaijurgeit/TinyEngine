#pragma once



namespace TE
{
    class Shader;
    class IndexBuffer;
    class VertexArray;
    
    class Renderer
    {
    public:
        Renderer();
        void Clear();

        void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
        void Draw(const VertexArray& vertexArray, const Shader& shader) const;
    };
}
