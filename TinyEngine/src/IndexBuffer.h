#pragma once
#include "glad/glad.h"

#include "Core.h"

namespace TE
{
    class TE_API IndexBuffer
    {
    public:
        IndexBuffer(const void* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        unsigned int GetCount() const { return Count; }
        
    private:
        unsigned int Id;
        unsigned int Count;
    };    
}
