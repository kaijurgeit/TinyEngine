#pragma once

namespace TE
{
    class VertexBuffer;
    class VertexArray;
    class VertexBufferLayout;
    
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
        unsigned int Id;
        void Foo(const VertexBuffer& vb, const VertexBufferLayout& layout);
    private:
    };    
}
