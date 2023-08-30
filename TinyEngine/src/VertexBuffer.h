#pragma once
#include "Core.h"

namespace TE
{
    class TE_API VertexBuffer
    {
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
        
    private:
        unsigned int id;
    };    
}
