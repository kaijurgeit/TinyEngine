#pragma once
#include "Core.h"

namespace TE
{
    class VertexBuffer;
    class VertexArray;
    class VertexBufferLayout;
    
    class TE_API VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;

    private:
        unsigned int Id;
    };    
}
